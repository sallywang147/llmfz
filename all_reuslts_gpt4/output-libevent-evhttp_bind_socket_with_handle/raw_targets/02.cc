#include <fuzzer/FuzzedDataProvider.h>
#include <event2/event.h>
#include <event2/http.h>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider fuzzed_data(data, size);

  // Initialize libevent.
  event_init();

  // Create a new evhttp object to handle requests.
  struct evhttp *http = evhttp_new(NULL);
  if (http == NULL) {
    return 0;
  }

  // Extract a string for the address.
  std::string address = fuzzed_data.ConsumeBytesAsString(fuzzed_data.ConsumeIntegralInRange<size_t>(0, 255));
  
  // Extract a short for the port.
  short port = fuzzed_data.ConsumeIntegral<short>();

  // Call the function under test.
  struct evhttp_bound_socket *bound_socket = evhttp_bind_socket_with_handle(http, const_cast<char*>(address.c_str()), port);

  // Clean up.
  if (bound_socket != NULL) {
    evhttp_del_accept_socket(http, bound_socket);
  }
  evhttp_free(http);

  return 0;
}