#include <fuzzer/FuzzedDataProvider.h>

#include <cstdint>
#include <cstdlib>

extern "C" {
#include <codec2/Codec.h>
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  Codec* codec = new Codec();
  int arg1 = stream.ConsumeIntegralInRange<int>(0, 100);
  int arg2 = stream.ConsumeIntegralInRange<int>(0, 100);
  int arg3 = stream.ConsumeIntegralInRange<int>(0, 100);
  int arg4 = stream.ConsumeIntegralInRange<int>(0, 100);
  int arg5 = stream.ConsumeIntegralInRange<int>(0, 100);
  int arg6 = stream.ConsumeIntegralInRange<int>(0, 100);
  int ret = codec->setXAACDRCInfo(codec, arg1, arg2, arg3, arg4, arg5, arg6);
  delete codec;
  return ret;
}