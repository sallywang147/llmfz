#include <amqp.h>
#include <arpa/inet.h>
#include <errno.h>
#include <netinet/in.h>
#include <pthread.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

#include <rabbitmq-c/amqp.h>
#include <rabbitmq-c/tcp_socket.h>

struct Fuzzer {
  int socket;
  uint16_t port;
  pthread_t thread;

  uint64_t size;
  uint8_t *buffer;
};
typedef struct Fuzzer Fuzzer;

#define PORT 5672
#define kMinInputLength 8
#define kMaxInputLength 1024

void client(Fuzzer *fuzzer);

void fuzzinit(Fuzzer *fuzzer) {
  struct sockaddr_in server_addr;
  int res;
  fuzzer->socket = socket(AF_INET, SOCK_STREAM, 0);
  if (fuzzer->socket == -1) {
    fprintf(stderr, "socket failed %s\n", strerror(errno));
    exit(1);
  }
  memset(&server_addr, 0, sizeof(server_addr));
  server_addr.sin_family = AF_INET;
  server_addr.sin_port = htons(fuzzer->port);
  server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
  res = setsockopt(fuzzer->socket, SOL_SOCKET, SO_REUSEADDR, &(int){1}, sizeof(int));
  if (res) {
    fprintf(stderr, "setsockopt failed: %s\n", strerror(errno));
    exit(1);
  }

  res = bind(fuzzer->socket, (struct sockaddr *)&server_addr, sizeof(server_addr));
  if (res) {
    fprintf(stderr, "bind failed: %s\n", strerror(errno));
    exit(1);
  }
  res = listen(fuzzer->socket, 1);
  if (res) {
    fprintf(stderr, "listen failed: %s\n", strerror(errno));
    exit(1);
  }
}

void *Server(void *args) {
  Fuzzer *fuzzer = (Fuzzer *)args;

  int client;
  int res;
  char clientData[10240];

  client = accept(fuzzer->socket, NULL, NULL);
  if (client == -1) {
    fprintf(stderr, "accept failed: %s\n", strerror(errno));
    exit(1);
  }

  res = recv(client, clientData, sizeof(clientData), 0);
  if (res == -1) {
    fprintf(stderr, "recv failed: %s\n", strerror(errno));
    exit(1);
  }
  res = send(client, fuzzer->buffer, fuzzer->size, 0);
  if (res == -1) {
    fprintf(stderr, "send failed: %s\n", strerror(errno));
    exit(1);
  }

  res = shutdown(client, SHUT_RDWR);
  close(client);
  return NULL;
}

void clean(Fuzzer *fuzzer) {
  shutdown(fuzzer->socket, SHUT_RDWR);
  close(fuzzer->socket);
  free(fuzzer->buffer);
  free(fuzzer);
}

extern "C" int LLVMFuzzerTestOneInput(const char *data, size_t size) {

  if (size < kMinInputLength || size > kMaxInputLength) {
    return 0;
  }

  Fuzzer *fuzzer = (Fuzzer *)malloc(sizeof(Fuzzer));
  fuzzer->port = PORT;

  fuzzer->size = size;
  fuzzer->buffer = malloc(fuzzer->size);
  memcpy(fuzzer->buffer, data, size);

  fuzzinit(fuzzer);

  pthread_create(&fuzzer->thread, NULL, Server, fuzzer);

  client(fuzzer);

  pthread_join(fuzzer->thread, NULL);

  clean(fuzzer);

  return 0;
}

void client(Fuzzer *fuzzer) {
  char const *hostname;
  int status;
  amqp_socket_t *socket = NULL;
  amqp_connection_state_t conn;
  amqp_rpc_reply_t reply;

  hostname = "127.0.0.1";

  conn = amqp_new_connection();

  socket = amqp_tcp_socket_new(conn);
  if (!socket) {
    exit(1);
  }

  status = amqp_socket_open(socket, hostname, fuzzer->port);
  if (status != AMQP_STATUS_OK) {
    int sav_errno = errno;
    fprintf(stderr, "amqp_socket_open failed: %s\n", amqp_error_string2(status));
    fprintf(stderr, "amqp_socket_open errno: %d: %s\n", sav_errno, strerror(sav_errno));
    exit(1);
  }

  amqp_login(conn, "/", 0, 131072, 0, AMQP_SASL_METHOD_PLAIN, "guest", "guest");

  amqp_connection_close(reply, conn, AMQP_REPLY_SUCCESS);

  amqp_destroy_connection(conn);
}