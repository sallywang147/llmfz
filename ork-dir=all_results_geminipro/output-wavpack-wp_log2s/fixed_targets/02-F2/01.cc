#include <fuzzer/FuzzedDataProvider.h>

#include <cstdint>
#include <cstdlib>

#include <wp_log2s.h>

extern "C" {
#include <wp_log2s.h>
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  const int value = stream.ConsumeIntegral<int>();
  wp_log2s(value);
  return 0;
}