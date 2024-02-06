#include <fuzzer/FuzzedDataProvider.h>

#include <cstdint>
#include <cstdlib>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  const int value = stream.ConsumeIntegral<int>();
  wp_log2s(value);
  return 0;
}