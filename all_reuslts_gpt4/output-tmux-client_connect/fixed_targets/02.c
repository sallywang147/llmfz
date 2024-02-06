#include <fuzzer/FuzzedDataProvider.h>
#include <event2/event.h>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider stream(data, size);

  struct event_base *base = event_base_new();
  if (base == NULL) {
    return 0;
  }

  std::string path = stream.ConsumeRandomLengthString();
  size_t flags = stream.ConsumeIntegral<size_t>();

  client_connect(base, const_cast<char*>(path.c_str()), flags);

  event_base_free(base);

  return 0;
}