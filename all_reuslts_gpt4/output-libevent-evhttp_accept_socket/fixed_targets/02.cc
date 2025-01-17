#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include <event2/event.h>
#include <event2/http.h>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  // Initialize libevent.
  struct event_base* base = event_base_new();
  if (base == nullptr) {
    return 0;
  }

  // Create a new evhttp server.
  struct evhttp* http = evhttp_new(base);
  if (http == nullptr) {
    event_base_free(base);
    return 0;
  }

  // Generate a socket file descriptor.
  int socket = stream.ConsumeIntegral<int>();

  // Call the target function.
  int result = evhttp_accept_socket(http, socket);

  // Cleanup.
  evhttp_free(http);
  event_base_free(base);

  return 0;
}