#include <fuzzer/FuzzedDataProvider.h>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider stream(data, size);

  while (stream.remaining_bytes() > 0) {
    int c = stream.ConsumeIntegral<int>();
    iswordchar(c);
  }

  return 0;
}