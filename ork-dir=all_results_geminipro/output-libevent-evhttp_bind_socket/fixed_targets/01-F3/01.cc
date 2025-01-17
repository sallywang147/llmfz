#include <assert.h>
#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>
#include <string>
#include <sys/socket.h>

#include <fuzzer/FuzzedDataProvider.h>

extern "C" {
#include "libevent/include/event2/buffer.h"
#include "libevent/include/event2/bufferevent.h"
#include "libevent/include/event2/event.h"
#include "libevent/include/event2/http.h"
#include "libevent/include/event2/http_struct.h"
#include "libevent/include/event2/listener.h"
#include "libevent/include/event2/util.h"
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {

  FuzzedDataProvider data_provider(data, size);

  std::string s1 = data_provider.ConsumeRandomLengthString();
  std::string s2 = data_provider.ConsumeRandomLengthString();
  size_t int1 = data_provider.ConsumeIntegral<size_t>();
  size_t int2 = data_provider.ConsumeIntegral<size_t>();
  size_t int3 = data_provider.ConsumeIntegral<size_t>();

  struct evhttp *httpd = NULL;
  struct evhttp_request *req = NULL;
  struct evhttp_connection *evcon = NULL;
  struct evbuffer *evbuf = NULL;
  struct sockaddr_in sin;

  /*create a server*/
  event_base *base = event_base_new();
  httpd = evhttp_start(base);
  if (!httpd) {
    return 0;
  }

  /*bind a socket*/
  memset(&sin, 0, sizeof(sin));
  sin.sin_family = AF_INET;
  sin.sin_port = htons(int2);
  assert(evhttp_bind_socket(httpd, s1.c_str(), int2) != -1);

  /*create a request*/
  req = evhttp_request_new(NULL, NULL);
  if (!req) {
    goto cleanup;
  }

  /*generate a request*/
  evhttp_add_header(req->output_headers, "Host", s2.c_str());
  evbuf = evbuffer_new();
  evbuffer_add_printf(evbuf, "Test data %d %d %d", int1, int2, int3);
  evhttp_add_header(req->output_headers, "Content-Type", "text/plain");
  evhttp_add_header(req->output_headers, "Content-Length", evbuffer_get_length(evbuf));
  evbuffer_prepend_buffer(req->output_buffer, evbuf);
  evbuffer_free(evbuf);

  /*send the request*/
  evcon = evhttp_connection_base_new(httpd, NULL, s1.c_str(), int2);
  if (!evcon) {
    goto cleanup;
  }
  evhttp_connection_set_timeout(evcon, int1);
  evhttp_make_request(evcon, req, EVHTTP_REQ_GET, "/test");

  /*clean up*/
cleanup:
  if (req) {
    evhttp_request_free(req);
  }
  if (evcon) {
    evhttp_connection_free(evcon);
  }
  if (httpd) {
    evhttp_free(httpd);
  }
  event_base_free(base);

  return 0;
}