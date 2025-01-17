#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "event2/event.h"
#include "event2/http.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  if (size < 1) {
    return 0;
  }

  FuzzedDataProvider provider(data, size);

  struct event_base *base = event_base_new();
  struct evhttp *http = evhttp_new(base);

  std::string address = provider.ConsumeRandomLengthString();
  short port = provider.ConsumeIntegral<short>();

  int result = evhttp_bind_socket(http, address.c_str(), port);

  evhttp_free(http);
  event_base_free(base);

  return 0;
}