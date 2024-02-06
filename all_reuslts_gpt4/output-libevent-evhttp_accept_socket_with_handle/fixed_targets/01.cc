#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>

#include <event2/event.h>
#include <event2/http.h>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  struct event_base *base = event_base_new();
  if (!base) {
    return 0;
  }

  struct evhttp *http = evhttp_new(base);
  if (!http) {
    event_base_free(base);
    return 0;
  }

  FuzzedDataProvider stream(data, size);
  int fd = stream.ConsumeIntegral<int>();

  struct evhttp_bound_socket *bound_socket = evhttp_accept_socket_with_handle(http, fd);

  if (bound_socket) {
    evhttp_del_accept_socket(http, bound_socket);
  }

  evhttp_free(http);
  event_base_free(base);
  return 0;
}