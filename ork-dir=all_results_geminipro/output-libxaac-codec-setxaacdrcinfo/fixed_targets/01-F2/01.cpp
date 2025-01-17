#include <fuzzer/FuzzedDataProvider.h>
#include <cstddef>
#include <cstdint>

namespace aac {

class Codec {
 public:
  int setXAACDRCInfo(Codec*, int, int, int, int, int) { return 0; }
};

}  // namespace aac

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  aac::Codec* codec = new aac::Codec();
  const int a = stream.ConsumeIntegral<int>();
  const int b = stream.ConsumeIntegral<int>();
  const int c = stream.ConsumeIntegral<int>();
  const int d = stream.ConsumeIntegral<int>();
  const int e = stream.ConsumeIntegral<int>();

  codec->setXAACDRCInfo(codec, a, b, c, d, e);
  delete codec;

  return 0;
}