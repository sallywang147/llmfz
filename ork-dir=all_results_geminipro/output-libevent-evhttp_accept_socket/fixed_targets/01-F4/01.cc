#include <assert.h>
#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>
#include <string>
#include <sys/socket.h>

#include <fuzzer/FuzzedDataProvider.h>

extern "C" {
#include "libevent/include/event2/event.h"
#include "libevent/include/event2/http.h"
#include "libevent/include/event2/bufferevent.h"
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {

  FuzzedDataProvider data_provider(data, size);

  std::string s1 = data_provider.ConsumeRandomLengthString();
  size_t int1 = data_provider.ConsumeIntegral<size_t>();
  size_t int2 = data_provider.ConsumeIntegral<size_t>();
  size_t int3 = data_provider.ConsumeIntegral<size_t>();

  struct event_base *base = NULL;
  struct evhttp *httpd = NULL;
  int fd = -1;

  /*create event base*/
  base = event_base_new();
  if (!base) {
    goto cleanup;
  }

  /*create http server*/
  httpd = evhttp_new(base);
  if (!httpd) {
    goto cleanup;
  }

  /*create socket*/
  fd = socket(AF_INET, SOCK_STREAM, 0);
  if (fd < 0) {
    goto cleanup;
  }

  /*make it non-blocking*/
  if (evutil_make_socket_nonblocking(fd) < 0) {
    goto cleanup;
  }

  /*accept socket*/
  assert(evhttp_accept_socket(httpd, fd) != -1);

  /*set some options*/
  evhttp_set_gencb(httpd, NULL, NULL);
  evhttp_set_timeout(httpd, int1);
  evhttp_set_max_body_size(httpd, int2);
  evhttp_set_max_headers(httpd, int3);

  /*clean up*/
cleanup:
  if (httpd) {
    evhttp_free(httpd);
  }
  if (base) {
    event_base_free(base);
  }
  if (fd != -1) {
    close(fd);
  }

  return 0;
}