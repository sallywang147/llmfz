#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  char arg1 = stream.ConsumeIntegral<char>();
  char arg2 = stream.ConsumeIntegral<char>();
  int arg3 = stream.ConsumeIntegral<int>();
  int arg4 = stream.ConsumeIntegral<int>();

  mscd_xfer_cb(arg1, arg2, arg3, arg4);

  return 0;
}