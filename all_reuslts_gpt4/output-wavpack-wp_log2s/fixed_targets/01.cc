#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>

extern "C" int wp_log2s(int value);

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider stream(data, size);
  int value = stream.ConsumeIntegral<int>();
  wp_log2s(value);
  return 0;
}