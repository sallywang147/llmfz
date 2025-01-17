#include <fuzzer/FuzzedDataProvider.h>

#include <cstdint>
#include <cstdlib>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  Codec* codec = new Codec();
  int arg1 = stream.ConsumeIntegral<int>();
  int arg2 = stream.ConsumeIntegral<int>();
  int arg3 = stream.ConsumeIntegral<int>();
  int arg4 = stream.ConsumeIntegral<int>();
  int arg5 = stream.ConsumeIntegral<int>();
  int arg6 = stream.ConsumeIntegral<int>();
  int ret = codec->setXAACDRCInfo(nullptr, arg1, arg2, arg3, arg4, arg5, arg6);
  delete codec;
  return ret;
}