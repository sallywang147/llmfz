#include <fuzzer/FuzzedDataProvider.h>
#include <ossfuzz/ossfuzz.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>

extern "C" {
#include <ossfuzz/ossfuzz.h>
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  const int debug_flags = stream.ConsumeIntegral<int>();
  ossfuzz_set_debug_flags(debug_flags);
  return 0;
}