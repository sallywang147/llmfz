#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>

extern "C" bool mscd_xfer_cb(char, char, int, int);

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider fuzzed_data(data, size);

  char arg1 = fuzzed_data.ConsumeIntegral<char>();
  char arg2 = fuzzed_data.ConsumeIntegral<char>();
  int arg3 = fuzzed_data.ConsumeIntegral<int>();
  int arg4 = fuzzed_data.ConsumeIntegral<int>();

  mscd_xfer_cb(arg1, arg2, arg3, arg4);

  return 0;
}