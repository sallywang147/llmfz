#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "event2/event.h"
#include "event2/http.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  static bool initialized = false;
  if (!initialized) {
    event_init();
    initialized = true;
  }

  FuzzedDataProvider provider(data, size);

  // Initialize evhttp object
  struct evhttp* http = evhttp_new(nullptr);
  if (http == nullptr) {
    return 0;
  }

  // Consume data for IP address
  std::string ip_address = provider.ConsumeBytesAsString(provider.ConsumeIntegralInRange<size_t>(0, 15));

  // Consume data for port
  short port = provider.ConsumeIntegral<short>();

  // Call the function
  struct evhttp_bound_socket* bound_socket = evhttp_bind_socket_with_handle(http, const_cast<char*>(ip_address.c_str()), port);

  // Cleanup
  if (bound_socket != nullptr) {
    evhttp_del_accept_socket(http, bound_socket);
  }
  evhttp_free(http);

  return 0;
}