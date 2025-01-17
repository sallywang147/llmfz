#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include <event2/event.h>
#include <event2/http.h>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  static bool initialized = false;
  if (!initialized) {
    evthread_use_pthreads();
    initialized = true;
  }

  FuzzedDataProvider provider(data, size);
  int socket = provider.ConsumeIntegral<int>();

  struct event_base *base = event_base_new();
  struct evhttp *http = evhttp_new(base);

  struct evhttp_bound_socket *bound_socket = evhttp_accept_socket_with_handle(http, socket);

  if (bound_socket != nullptr) {
    evhttp_del_accept_socket(http, bound_socket);
  }

  evhttp_free(http);
  event_base_free(base);

  return 0;
}