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
#include "libevent/include/event2/util.h"
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {

  FuzzedDataProvider data_provider(data, size);

  std::string s1 = data_provider.ConsumeRandomLengthString();
  size_t int1 = data_provider.ConsumeIntegral<size_t>();
  size_t int2 = data_provider.ConsumeIntegral<size_t>();
  size_t int3 = data_provider.ConsumeIntegral<size_t>();
  size_t int4 = data_provider.ConsumeIntegral<size_t>();

  struct evhttp *http = NULL;
  struct evhttp_connection *evcon = NULL;
  struct evhttp_request *req = NULL;

  /*create an http object*/
  http = evhttp_new(NULL);
  if (!http) {
    return 0;
  }

  /*bind socket*/
  int ret = evhttp_bind_socket(http, s1.c_str(), int1);
  if (ret == -1) {
    assert(false);
  }

  /*create a connection*/
  evcon = evhttp_connection_base_new(http, NULL, s1.c_str(), int1);
  if (!evcon) {
    goto cleanup;
  }

  /*create a request*/
  req = evhttp_request_new(NULL, NULL);
  if (!req) {
    goto cleanup;
  }

  /*send request*/
  evhttp_connection_send_request(evcon, req, EVHTTP_REQ_GET, "/");

  /*get response*/
  evhttp_connection_set_timeout(evcon, int2);
  evhttp_connection_set_max_body_size(evcon, int3);
  evhttp_connection_set_max_headers_size(evcon, int4);

  struct evbuffer *buf = evhttp_connection_get_input_buffer(evcon);
  size_t len = evbuffer_get_length(buf);
  if (len > 0) {
    char *data = (char *)evbuffer_pullup(buf, len);
    if (data) {
      // Do something with the data
    }
  }

  evhttp_connection_free(evcon);
  evhttp_request_free(req);

  /*clean up*/
cleanup:
  if (http) {
    evhttp_free(http);
  }

  return 0;
}