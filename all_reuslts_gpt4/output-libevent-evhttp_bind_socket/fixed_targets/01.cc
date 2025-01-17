#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>

#include <event2/event.h>
#include <event2/http.h>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  if (size < 2) {
    return 0;
  }
  
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

  // Extracting the port number from the stream
  short port = stream.ConsumeIntegral<short>();

  // Extracting the address from the stream
  std::string address = stream.ConsumeRemainingBytesAsString();

  // Attempting to bind the socket
  evhttp_bind_socket(http, const_cast<char*>(address.c_str()), port);

  evhttp_free(http);
  event_base_free(base);

  return 0;
}