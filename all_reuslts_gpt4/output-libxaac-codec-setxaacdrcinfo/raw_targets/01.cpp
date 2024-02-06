#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>

#include "Codec.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  Codec codec;

  int arg1 = stream.ConsumeIntegral<int>();
  int arg2 = stream.ConsumeIntegral<int>();
  int arg3 = stream.ConsumeIntegral<int>();
  int arg4 = stream.ConsumeIntegral<int>();
  int arg5 = stream.ConsumeIntegral<int>();

  codec.setXAACDRCInfo(&codec, arg1, arg2, arg3, arg4, arg5);

  return 0;
}