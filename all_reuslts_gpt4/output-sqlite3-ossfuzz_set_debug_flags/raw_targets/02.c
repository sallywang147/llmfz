#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>

extern "C" void ossfuzz_set_debug_flags(int x);

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  int x = stream.ConsumeIntegral<int>();
  ossfuzz_set_debug_flags(x);
  return 0;
}