#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include <event2/event.h>
#include <event2/http.h>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  if (size == 0) {
    return 0;
  }

  FuzzedDataProvider stream(data, size);

  struct event_base *base = event_base_new();
  if (!base) {
    return 0;
  }

  struct evhttp *http = evhttp_new(base);
  if (!http) {
    event_base_free(base);
    return 0;
  }

  int socket = stream.ConsumeIntegral<int>();
  evhttp_accept_socket(http, socket);

  evhttp_free(http);
  event_base_free(base);

  return 0;
}