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
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {

  FuzzedDataProvider data_provider(data, size);

  std::string s1 = data_provider.ConsumeRandomLengthString();
  size_t int1 = data_provider.ConsumeIntegral<size_t>();
  size_t int2 = data_provider.ConsumeIntegral<size_t>();

  struct evhttp *http = NULL;
  struct evhttp_bound_socket *bound_socket = NULL;
  struct evconnlistener *listener = NULL;
  struct event_base *base = NULL;
  struct sockaddr_in sin;

  base = event_base_new();
  http = evhttp_new(base);
  evhttp_set_gencb(http, NULL, NULL);

  /*bind socket*/
  memset(&sin, 0, sizeof(sin));
  sin.sin_family = AF_INET;
  sin.sin_addr.s_addr = htonl(INADDR_ANY);
  sin.sin_port = htons(int1);

  bound_socket = evhttp_bind_socket_with_handle(http, s1.c_str(), int1);
  assert(bound_socket != NULL);

  listener = evhttp_bound_socket_get_listener(bound_socket);
  evconnlistener_set_cb(listener, NULL, NULL, NULL, NULL);

  /*clean up*/
  evhttp_free(http);
  event_base_free(base);

  return 0;
}