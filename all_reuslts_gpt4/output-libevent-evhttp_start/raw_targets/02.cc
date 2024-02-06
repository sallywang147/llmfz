#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "event2/event.h"
#include "event2/http.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  // Extract a string for the address. We use a maximum size of 255 to avoid overly long strings.
  std::string address = stream.ConsumeBytesAsString(stream.ConsumeIntegralInRange<uint8_t>(0, 255));
  
  // Extract a short for the port number. We limit the range to avoid privileged ports.
  short port = stream.ConsumeIntegralInRange<short>(1024, 65535);

  // Start the HTTP server
  struct evhttp *http = evhttp_start(address.c_str(), port);

  // Clean up
  if (http) {
    evhttp_free(http);
  }

  return 0;
}