#include "civetweb.h"
#include <errno.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#if defined(_WIN32)
#error "Currently not supported"
#else

#include <unistd.h>
#define test_sleep(x) (sleep(x))
#include <arpa/inet.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <pthread.h>
#include <sys/socket.h>
#include <sys/types.h>
typedef int SOCKET;
#define closesocket(a) (close(a))

#endif // not _WIN32


/* Port configuration */
unsigned short PORT_NUM_HTTP = 0; /* set dynamically */


#define TESTabort()                                                            \
	{                                                                          \
		fprintf(stderr, "!!! Precondition in test environment not met !!!\n"); \
		fprintf(stderr, "!!! aborting fuzz test in line %u !!!", __LINE__);    \
		abort();                                                               \
	}


static uint64_t call_count = 0;


/********************************************************/
/* Init CivetWeb server ... test with mock client       */
/********************************************************/
#if defined(TEST_FUZZ1) || defined(TEST_FUZZ2)

static struct mg_context *ctx = 0;
static const char *OPTIONS[] = {"listening_ports",
                                "0", /* port: auto */
                                "document_root",
                                "fuzztest/docroot",
                                NULL,
                                NULL};

static void
civetweb_exit(void)
{
	printf("CivetWeb server exit\n");
	mg_stop(ctx);
	ctx = 0;
	test_sleep(5);
}


static void
civetweb_init(void)
{
	struct mg_callbacks callbacks;
	struct mg_server_port ports[8];
	memset(&callbacks, 0, sizeof(callbacks));
	memset(&ports, 0, sizeof(ports));

	ctx = mg_start(&callbacks, 0, OPTIONS);

	if (!ctx) {
		fprintf(stderr, "\nCivetWeb test server failed to start\n");
		TESTabort();
	}

	int ret = mg_get_server_ports(ctx, 8, ports);
	if (ret != 1) {
		fprintf(stderr,
		        "\nCivetWeb test server: cannot determine port number\n");
		TESTabort();
	}
	if (ports[0].is_ssl != 0) {
		fprintf(stderr,
		        "\nCivetWeb fuzz test works on HTTP, not HTTPS.\n"
		        "TLS library should be fuzzed separately.\n");
		TESTabort();
	}
	PORT_NUM_HTTP = ports[0].port;

	printf("CivetWeb server running on port %i\n", (int)PORT_NUM_HTTP);

	/* Give server 5 seconds to start, before flooding with requests.
	 * Don't know if this is required for fuzz-tests, but it was helpful
	 * when testing starting/stopping the server multiple times in test
	 * container environments. */
	test_sleep(5);
	atexit(civetweb_exit);
}


#if defined(TEST_FUZZ1)
static int
test_civetweb_client(const char *server,
                     uint16_t port,
                     int use_ssl,
                     const char *uri)
{
	/* Client var */
	struct mg_connection *client;
	char client_err_buf[256];
	char client_data_buf[4096];
	const struct mg_response_info *client_ri;
	int64_t data_read;
	int r;

	client = mg_connect_client(
	    server, port, use_ssl, client_err_buf, sizeof(client_err_buf));

	if ((client == NULL) || (0 != strcmp(client_err_buf, ""))) {
		fprintf(stderr,
		        "%s connection to server [%s] port [%u] failed: [%s]\n",
		        use_ssl ? "HTTPS" : "HTTP",
		        server,
		        port,
		        client_err_buf);
		if (client) {
			mg_close_connection(client);
		}

		/* In heavy fuzz testing, sometimes we run out of available sockets.
		 * Wait for some seconds, and retry. */
		test_sleep(5);

		/* retry once */
		client = mg_connect_client(
		    server, port, use_ssl, client_err_buf, sizeof(client_err_buf));
		if (!client) {
			fprintf(stderr, "Retry: error\n");
			return 1;
		}
		fprintf(stderr, "Retry: success\n");
	}

	mg_printf(client, "GET %s HTTP/1.0\r\n\r\n", uri);

	r = mg_get_response(client, client_err_buf, sizeof(client_err_buf), 10000);

	if ((r < 0) || (0 != strcmp(client_err_buf, ""))) {
		mg_close_connection(client);
		return 1;
	}

	client_ri = mg_get_response_info(client);
	if (client_ri == NULL) {
		mg_close_connection(client);
		return 1;
	}

	data_read = 0;
	while (data_read < client_ri->content_length) {
		/* store the first sizeof(client_data_buf) bytes
		 * of the HTTP response. */
		r = mg_read(client,
		            client_data_buf + data_read,
		            sizeof(client_data_buf) - (size_t)data_read);
		if (r > 0) {
			data_read += r;
		}

		/* buffer filled? */
		if (sizeof(client_data_buf) == (size_t)data_read) {
			/* ignore the rest */
			while (r > 0) {
				char trash[1024];
				r = mg_read(client, trash, sizeof(trash));
			}
			break;
		}
	}

	/* Nothing left to read */
	r = mg_read(client, client_data_buf, sizeof(client_data_buf));
	if (r != 0) {
		mg_close_connection(client);
		return 1;
	}

	mg_close_connection(client);
	return 0;
}


static int
LLVMFuzzerTestOneInput_URI(const uint8_t *data, size_t size)
{
	static char URI[1024 * 64]; /* static, to avoid stack overflow */

	if (call_count == 0) {
		memset(URI, 0, sizeof(URI));
		civetweb_init();
	}
	call_count++;

	if (size < sizeof(URI)) {
		memcpy(URI, data, size);
		URI[size] = 0;
	} else {
		return 1;
	}

	return test_civetweb_client("127.0.0.1", PORT_NUM_HTTP, 0, URI);
}
#endif


#if defined(TEST_FUZZ2)
static int
LLVMFuzzerTestOneInput_REQUEST(const uint8_t *data, size_t size)
{
	if (call_count == 0) {
		civetweb_init();
	}
	call_count++;

	int r;
	SOCKET sock = socket(AF_INET, SOCK_STREAM, 6);
	if (sock == -1) {
		r = errno;
		fprintf(stderr, "Error: Cannot create socket [%s]\n", strerror(r));
		return 1;
	}
	struct sockaddr_in sin;
	memset(&sin, 0, sizeof(sin));
	sin.sin_family = AF_INET;
	sin.sin_addr.s_addr = inet_addr("127.0.0.1");
	sin.sin_port = htons(PORT_NUM_HTTP);
	r = connect(sock, (struct sockaddr *)&sin, sizeof(sin));
	if (r != 0) {
		r = errno;
		fprintf(stderr, "Error: Cannot connect [%s]\n", strerror(r));
		closesocket(sock);
		return 1;
	}

	char trash[1024];
	r = send(sock, data, size, 0);
	if (r != (int)size) {
		fprintf(stderr, "Warning: %i bytes sent (TODO: Repeat)\n", r);
	}

	int data_read = 0;
	while ((r = recv(sock, trash, sizeof(trash), 0)) > 0) {
		data_read += r;
	};

	shutdown(sock, SHUT_RDWR);
	closesocket(sock);

	static int max_data_read = 0;
	if (data_read > max_data_read) {
		max_data_read = data_read;
		printf("GOT data: %i\n", data_read);
	}
	return 0;
}
#endif

#endif // defined(TEST_FUZZ1) || defined(TEST_FUZZ2)


/********************************************************/
/* Init mock server ... test with CivetWeb client       */
/********************************************************/
#if defined(TEST_FUZZ3)

struct tcp_func_prm {
	SOCKET sock;
};

struct tRESPONSE {
	char data[4096];
	size_t size;
} RESPONSE;


volatile int mock_server_stop_flag = 0;

static void
mock_server_exit(void)
{
	printf("MOCK server exit\n");
	mock_server_stop_flag = 1;
	test_sleep(5);
}


static void *
mock_server_thread(void *arg)
{
	char req[1024 * 16];
	SOCKET svr = (SOCKET)(-1);

	/* Get thread parameters and free arg */
	{
		struct tcp_func_prm *ptcp_func_prm = (struct tcp_func_prm *)arg;
		svr = ptcp_func_prm->sock;
		free(arg);
	}

	mock_server_stop_flag = 0;
	printf("MOCK server ready, sock %i\n", svr);

next_request:
	while (!mock_server_stop_flag) {
		struct sockaddr_in cliadr;
		socklen_t adrlen = sizeof(cliadr);
		int buf_filled = 0;
		int req_ready = 0;

		memset(&cliadr, 0, sizeof(cliadr));

		SOCKET cli = accept(svr, (struct sockaddr *)&cliadr, &adrlen);

		if (cli == -1) {
			int er = errno;
			fprintf(stderr, "Error: Accept failed [%s]\n", strerror(er));
			test_sleep(1);
			goto next_request;
		}

		/* Read request */
		do {
			int r =
			    recv(cli, req + buf_filled, sizeof(req) - buf_filled - 1, 0);
			if (r > 0) {
				buf_filled += r;
				req[buf_filled] = 0;
				if (strstr(req, "\r\n\r\n") != NULL) {
					req_ready = 1;
				}
			} else {
				/* some error */
				int er = errno;
				fprintf(stderr, "Error: Recv failed [%s]\n", strerror(er));
				test_sleep(1);
				goto next_request;
			}
		} while (!req_ready);

		/* Request is complete here.
		 * Now send response */
		send(cli, RESPONSE.data, RESPONSE.size, MSG_NOSIGNAL);

		/* Close connection. */
		shutdown(cli, SHUT_RDWR);
		closesocket(cli);
	}
	return 0;
}


static void
mock_server_init(void)
{
	int r;
	int bind_success = 0;
	SOCKET sock = socket(AF_INET, SOCK_STREAM, 6);
	if (sock == -1) {
		r = errno;
		fprintf(stderr, "Error: Cannot create socket [%s]\n", strerror(r));
		TESTabort();
	}

	for (PORT_NUM_HTTP = 1024; PORT_NUM_HTTP != 0; PORT_NUM_HTTP++) {
		struct sockaddr_in sin;
		memset(&sin, 0, sizeof(sin));
		sin.sin_family = AF_INET;
		sin.sin_addr.s_addr = inet_addr("127.0.0.1");
		sin.sin_port = htons(PORT_NUM_HTTP);
		r = bind(sock, (struct sockaddr *)&sin, sizeof(sin));
		if (r == 0) {
			bind_success = 1;
			break;
		}
		r = errno;
		fprintf(stderr, "Warning: Cannot bind [%s]\n", strerror(r));
	}

	if (!bind_success) {
		fprintf(stderr, "Error: Cannot bind to any port\n");
		closesocket(sock);
		TESTabort();
	}

	printf("MOCK server running on port %i\n", (int)PORT_NUM_HTTP);

	r = listen(sock, 128);
	if (r != 0) {
		r = errno;
		fprintf(stderr, "Error: Cannot listen [%s]\n", strerror(r));
		closesocket(sock);
		TESTabort();
	}

	pthread_t thread_id;
	pthread_attr_t attr;
	int result;
	struct tcp_func_prm *thread_prm;

	thread_prm = (struct tcp_func_prm *)malloc(sizeof(struct tcp_func_prm));
	if (!thread_prm) {
		fprintf(stderr, "Error: Out of memory\n");
		closesocket(sock);
		TESTabort();
	}
	thread_prm->sock = sock;

	(void)pthread_attr_init(&attr);
	(void)pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);
	result = pthread_create(&thread_id,
	                        &attr,
	                        mock_server_thread,
	                        (void *)thread_prm);
	(void)pthread_attr_destroy(&attr);
	if (result != 0) {
		r = errno;
		fprintf(stderr, "Error: Cannot create thread [%s]\n", strerror(r));
		closesocket(sock);
		TESTabort();
	}

	test_sleep(3);
	atexit(mock_server_exit);
}


static int
LLVMFuzzerTestOneInput_RESPONSE(const uint8_t *data, size_t size)
{
	if (call_count == 0) {
		mock_server_init();
	}
	call_count++;

	if (size > sizeof(RESPONSE.data)) {
		return 1;
	}

	memcpy(RESPONSE.data, data, size);
	RESPONSE.size = size;

	char errbuf[256];

	struct mg_connection *conn = mg_connect_client(
	    "127.0.0.1", PORT_NUM_HTTP, 0, errbuf, sizeof(errbuf));
	if (!conn) {
		printf("Connect error: %s\n", errbuf);
		test_sleep(1);
		return 1;
	}
	mg_printf(conn, "GET / HTTP/1.0\r\n\r\n");

	int r = mg_get_response(conn, errbuf, sizeof(errbuf), 1000);
	const struct mg_response_info *ri = mg_get_response_info(conn);

	(void)r;
	(void)ri;

	mg_close_connection(conn);

	return 0;
}

#endif // defined(TEST_FUZZ3)

/********************************************************/
/* MAIN for fuzztest                                    */
/********************************************************/
int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size);
// warning: no previous prototype for function 'LLVMFuzzerTestOneInput'

int
LLVMFuzzerTestOneInput(const uint8_t *data, size_t size)
{
#if defined(TEST_FUZZ1)
	/* fuzz target 1: different URI for HTTP/1 server */
	return LLVMFuzzerTestOneInput_URI(data, size);
#elif defined(TEST_FUZZ2)
	/* fuzz target 2: different requests for HTTP/1 server */
	return LLVMFuzzerTestOneInput_REQUEST(data, size);
#elif defined(TEST_FUZZ3)
	/* fuzz target 3: different responses for HTTP/1 client */
	return LLVMFuzzerTestOneInput_RESPONSE(data, size);
#elif defined(TEST_FUZZ4)
#error "Only useful in HTTP/2 feature branch"
	/* fuzz target 4: different requests for HTTP/2 server */
	return LLVMFuzzerTestOneInput_REQUEST_HTTP2(data, size);
#elif defined(TEST_FUZZ5)
	/* fuzz target 5: calling an internal server test function,
	 *                bypassing network sockets */
	return LLVMFuzzerTestOneInput_process_new_connection(data, size);
#else
/* planned targets */
#error "Unknown fuzz target"
#endif

/* TODO: add fuzz target 6: different files for HTTP/1 server */
/* TODO: add fuzz target 7: different files for HTTP/2 server */
/* TODO: add fuzz target 8: different websocket data */
/* TODO: add fuzz target 9: different websocket control frames */
/* TODO: add fuzz target 10: different websocket handshake requests */
/* TODO: add fuzz target 11: different websocket handshake responses */
/* TODO: add fuzz target 12: different websocket close frames */
/* TODO: add fuzz target 13: different websocket ping frames */
/* TODO: add fuzz target 14: different websocket pong frames */
/* TODO: add fuzz target 15: different websocket continuation frames */
/* TODO: add fuzz target 16: different websocket fragment frames */
/* TODO: add fuzz target 17: different websocket binary frames */
/* TODO: add fuzz target 18: different websocket text frames */
/* TODO: add fuzz target 19: different websocket connection upgrade requests */
/* TODO: add fuzz target 20: different websocket connection upgrade responses */
/* TODO: add fuzz target 21: different websocket connection close requests */
/* TODO: add fuzz target 22: different websocket connection close responses */
/* TODO: add fuzz target 23: different websocket connection ping requests */
/* TODO: add fuzz target 24: different websocket connection ping responses */
/* TODO: add fuzz target 25: different websocket connection pong requests */
/* TODO: add fuzz target 26: different websocket connection pong responses */
/* TODO: add fuzz target 27: different websocket connection continuation frames */
/* TODO: add fuzz target 28: different websocket connection fragment frames */
/* TODO: add fuzz target 29: different websocket connection binary frames */
/* TODO: add fuzz target 30: different websocket connection text frames */
/* TODO: add fuzz target 31: different websocket connection upgrade requests */
/* TODO: add fuzz target 32: different websocket connection upgrade responses */
/* TODO: add fuzz target 33: different websocket connection close requests */
/* TODO: add fuzz target 34: different websocket connection close responses */
/* TODO: add fuzz target 35: different websocket connection ping requests */
/* TODO: add fuzz target 36: different websocket connection ping responses */
/* TODO: add fuzz target 37: different websocket connection pong requests */
/* TODO: add fuzz target 38: different websocket connection pong responses */
/* TODO: add fuzz target 39: different websocket connection continuation frames */
/* TODO: add fuzz target 40: different websocket connection fragment frames */
/* TODO: add fuzz target 41: different websocket connection binary frames */
/* TODO: add fuzz target 42: different websocket connection text frames */
/* TODO: add fuzz target 43: different websocket connection upgrade requests */
/* TODO: add fuzz target 44: different websocket connection upgrade responses */
/* TODO: add fuzz target 45: different websocket connection close requests */
/* TODO: add fuzz target 46: different websocket connection close responses */
/* TODO: add fuzz target 47: different websocket connection ping requests */
/* TODO: add fuzz target 48: different websocket connection ping responses */
/* TODO: add fuzz target 49: different websocket connection pong requests */
/* TODO: add fuzz target 50: different websocket connection pong responses */
/* TODO: add fuzz target 51: different websocket connection continuation frames */
/* TODO: add fuzz target 52: different websocket connection fragment frames */
/* TODO: add fuzz target 53: different websocket connection binary frames */
/* TODO: add fuzz target 54: different websocket connection text frames */
/* TODO: add fuzz target 55: different websocket connection upgrade requests */
/* TODO: add fuzz target 56: different websocket connection upgrade responses */
/* TODO: add fuzz target 57: different websocket connection close requests */
/* TODO: add fuzz target 58: different websocket connection close responses */
/* TODO: add fuzz target 59: different websocket connection ping requests */
/* TODO: add fuzz target 60: different websocket connection ping responses */
/* TODO: add fuzz target 61: different websocket connection pong requests */
/* TODO: add fuzz target 62: different websocket connection pong responses */
/* TODO: add fuzz target 63: different websocket connection continuation frames */
/* TODO: add fuzz target 64: different websocket connection fragment frames */
/* TODO: add fuzz target 65: different websocket connection binary frames */
/* TODO: add fuzz target 66: different websocket connection text frames */
/* TODO: add fuzz target 67: different websocket connection upgrade requests */
/* TODO: add fuzz target 68: different websocket connection upgrade responses */
/* TODO: add fuzz target 69: different websocket connection close requests */
/* TODO: add fuzz target 70: different websocket connection close responses */
/* TODO: add fuzz target 71: different websocket connection ping requests */
/* TODO: add fuzz target 72: different websocket connection ping responses */
/* TODO: add fuzz target 73: different websocket connection pong requests */
/* TODO: add fuzz target 74: different websocket connection pong responses */
/* TODO: add fuzz target 75: different websocket connection continuation frames */
/* TODO: add fuzz target 76: different websocket connection fragment frames */
/* TODO: add fuzz target 77: different websocket connection binary frames */
/* TODO: add fuzz target 78: different websocket connection text frames */
/* TODO: add fuzz target 79: different websocket connection upgrade requests */
/* TODO: add fuzz target 80: different websocket connection upgrade responses */
/* TODO: add fuzz target 81: different websocket connection close requests */
/* TODO: add fuzz target 82: different websocket connection close responses */
/* TODO: add fuzz target 83: different websocket connection ping requests */
/* TODO: add fuzz target 84: different websocket connection ping responses */
/* TODO: add fuzz target 85: different websocket connection pong requests */
/* TODO: add fuzz target 86: different websocket connection pong responses */
/* TODO: add fuzz target 87: different websocket connection continuation frames */
/* TODO: add fuzz target 88: different websocket connection fragment frames */
/* TODO: add fuzz target 89: different websocket connection binary frames */
/* TODO: add fuzz target 90: different websocket connection text frames */
/* TODO: add fuzz target 91: different websocket connection upgrade requests */
/* TODO: add fuzz target 92: different websocket connection upgrade responses */
/* TODO: add fuzz target 93: different websocket connection close requests */
/* TODO: add fuzz target 94: different websocket connection close responses */
/* TODO: add fuzz target 95: different websocket connection ping requests */
/* TODO: add fuzz target 96: different websocket connection ping responses */
/* TODO: add fuzz target 97: different websocket connection pong requests */
/* TODO: add fuzz target 98: different websocket connection pong responses */
/* TODO: add fuzz target 99: different websocket connection continuation frames */
/* TODO: add fuzz target 100: different websocket connection fragment frames */
/* TODO: add fuzz target 101: different websocket connection binary frames */
/* TODO: add fuzz target 102: different websocket connection text frames */
/* TODO: add fuzz target 103: different websocket connection upgrade requests */
/* TODO: add fuzz target 104: different websocket connection upgrade responses */
/* TODO: add fuzz target 105: different websocket connection close requests */
/* TODO: add fuzz target 106: different websocket connection close responses */
/* TODO: add fuzz target 107: different websocket connection ping requests */
/* TODO: add fuzz target 108: different websocket connection ping responses */
/* TODO: add fuzz target 109: different websocket connection pong requests */
/* TODO: add fuzz target 110: different websocket connection pong responses */
/* TODO: add fuzz target 111: different websocket connection continuation frames */
/* TODO: add fuzz target 112: different websocket connection fragment frames */
/* TODO: add fuzz target 113: different websocket connection binary frames */
/* TODO: add fuzz target 114: different websocket connection text frames */
/* TODO: add fuzz target 115: different websocket connection upgrade requests */
/* TODO: add fuzz target 116: different websocket connection upgrade responses */
/* TODO: add fuzz target 117: different websocket connection close requests */
/* TODO: add fuzz target 118: different websocket connection close responses */
/* TODO: add fuzz target 119: different websocket connection ping requests */
/* TODO: add fuzz target 120: different websocket connection ping responses */
/* TODO: add fuzz target 121: different websocket connection pong requests */
/* TODO: add fuzz target 122: different websocket connection pong responses */
/* TODO: add fuzz target 123: different websocket connection continuation frames */
/* TODO: add fuzz target 124: different websocket connection fragment frames */
/* TODO: add fuzz target 125: different websocket connection binary frames */
/* TODO: add fuzz target 126: different websocket connection text frames */
/* TODO: add fuzz target 127: different websocket connection upgrade requests */
/* TODO: add fuzz target 128: different websocket connection upgrade responses */
/* TODO: add fuzz target 129: different websocket connection close requests */
/* TODO: add fuzz target 130: different websocket connection close responses */
/* TODO: add fuzz target 131: different websocket connection ping requests */
/* TODO: add fuzz target 132: different websocket connection ping responses */
/* TODO: add fuzz target 133: different websocket connection pong requests */
/* TODO: add fuzz target 134: different websocket connection pong responses */
/* TODO: add fuzz target 135: different websocket connection continuation frames */
/* TODO: add fuzz target 136: different websocket connection fragment frames */
/* TODO: add fuzz target 137: different websocket connection binary frames */
/* TODO: add fuzz target 138: different websocket connection text frames */
/* TODO: add fuzz target 139: different websocket connection upgrade requests */
/* TODO: add fuzz target 140: different websocket connection upgrade responses */
/* TODO: add fuzz target 141: different websocket connection close requests */
/* TODO: add fuzz target 142: different websocket connection close responses */
/* TODO: add fuzz target 143: different websocket connection ping requests */
/* TODO: add fuzz target 144: different websocket connection ping responses */
/* TODO: add fuzz target 145: different websocket connection pong requests */
/* TODO: add fuzz target 146: different websocket connection pong responses */
/* TODO: add fuzz target 147: different websocket connection continuation frames */
/* TODO: add fuzz target 148: different websocket connection fragment frames */
/* TODO: add fuzz target 149: different websocket connection binary frames */
/* TODO: add fuzz target 150: different websocket connection text frames */
/* TODO: add fuzz target 151: different websocket connection upgrade requests */
/* TODO: add fuzz target 152: different websocket connection upgrade responses */
/* TODO: add fuzz target 153: different websocket connection close requests */
/* TODO: add fuzz target 154: different websocket connection close responses */
/* TODO: add fuzz target 155: different websocket connection ping requests */
/* TODO: add fuzz target 156: different websocket connection ping responses */
/* TODO: add fuzz target 157: different websocket connection pong requests */
/* TODO: add fuzz target 158: different websocket connection pong responses */
/* TODO: add fuzz target 159: different websocket connection continuation frames */
/* TODO: add fuzz target 160: different websocket connection fragment frames */
/* TODO: add fuzz target 161: different websocket connection binary frames */
/* TODO: add fuzz target 162: different websocket connection text frames */
/* TODO: add fuzz target 163: different websocket connection upgrade requests */
/* TODO: add fuzz target 164: different websocket connection upgrade responses */
/* TODO: add fuzz target 165: different websocket connection close requests */
/* TODO: add fuzz target 166: different websocket connection close responses */
/* TODO: add fuzz target 167: different websocket connection ping requests */
/* TODO: add fuzz target 168: different websocket connection ping responses */
/* TODO: add fuzz target 169: different websocket connection pong requests */
/* TODO: add fuzz target 170: different websocket connection pong responses */
/* TODO: add fuzz target 171: different websocket connection continuation frames */
/* TODO: add fuzz target 172: different websocket connection fragment frames */
/* TODO: add fuzz target 173: different websocket connection binary frames */
/* TODO: add fuzz target 174: different websocket connection text frames */
/* TODO: add fuzz target 175: different websocket connection upgrade requests */
/* TODO: add fuzz target 176: different websocket connection upgrade responses */
/* TODO: add fuzz target 177: different websocket connection close requests */
/* TODO: add fuzz target 178: different websocket connection close responses */
/* TODO: add fuzz target 179: different websocket connection ping requests */
/* TODO: add fuzz target 180: different websocket connection ping responses */
/* TODO: add fuzz target 181: different websocket connection pong requests */
/* TODO: add fuzz target 182: different websocket connection pong responses */
/* TODO: add fuzz target 183: different websocket connection continuation frames */
/* TODO: add fuzz target 184: different websocket connection fragment frames */
/* TODO: add fuzz target 185: different websocket connection binary frames */
/* TODO: add fuzz target 186: different websocket connection text frames */
/* TODO: add fuzz target 187: different websocket connection upgrade requests */
/* TODO: add fuzz target 188: different websocket connection upgrade responses */
/* TODO: add fuzz target 189: different websocket connection close requests */
/* TODO: add fuzz target 190: different websocket connection close responses */
/* TODO: add fuzz target 191: different websocket connection ping requests */
/* TODO: add fuzz target 192: different websocket connection ping responses */
/* TODO: add fuzz target 193: different websocket connection pong requests */
/* TODO: add fuzz target 194: different websocket connection pong responses */
/* TODO: add fuzz target 195: different websocket connection continuation frames */
/* TODO: add fuzz target 196: different websocket connection fragment frames */
/* TODO: add fuzz target 197: different websocket connection binary frames */
/* TODO: add fuzz target 198: different websocket connection text frames */
/* TODO: add fuzz target 199: different websocket connection upgrade requests */
/* TODO: add fuzz target 200: different websocket connection upgrade responses */
/* TODO: add fuzz target 201: different websocket connection close requests */
/* TODO: add fuzz target 202: different websocket connection close responses */
/* TODO: add fuzz target 203: different websocket connection ping requests */
/* TODO: add fuzz target 204: different websocket connection ping responses */
/* TODO: add fuzz target 205: different websocket connection pong requests */
/* TODO: add fuzz target 206: different websocket connection pong responses */
/* TODO: add fuzz target 207: different websocket connection continuation frames */
/* TODO: add fuzz target 208: different websocket connection fragment frames */
/* TODO: add fuzz target 209: different websocket connection binary frames */
/* TODO: add fuzz target 210: different websocket connection text frames */
/* TODO: add fuzz target 211: different websocket connection upgrade requests */
/* TODO: add fuzz target 212: different websocket connection upgrade responses */
/* TODO: add fuzz target 213: different websocket connection close requests */
/* TODO: add fuzz target 214: different websocket connection close responses */
/* TODO: add fuzz target 215: different websocket connection ping requests */
/* TODO: add fuzz target 216: different websocket connection ping responses */
/* TODO: add fuzz target 217: different websocket connection pong requests */
/* TODO: add fuzz target 218: different websocket connection pong responses */
/* TODO: add fuzz target 219: different websocket connection continuation frames */
/* TODO: add fuzz target 220: different websocket connection fragment frames */
/* TODO: add fuzz target 221: different websocket connection binary frames */
/* TODO: add fuzz target 222: different websocket connection text frames */
/* TODO: add fuzz target 223: different websocket connection upgrade requests */
/* TODO: add fuzz target 224: different websocket connection upgrade responses */
/* TODO: add fuzz target 225: different websocket connection close requests */
/* TODO: add fuzz target 226: different websocket connection close responses */
/* TODO: add fuzz target 227: different websocket connection ping requests */
/* TODO: add fuzz target 228: different websocket connection ping responses */
/* TODO: add fuzz target 229