#include <fuzzer/FuzzedDataProvider.h>

#include <cstdint>
#include <cstring>
#include <string>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  const std::string filename = stream.ConsumeBytesAsString(16);
  const std::string image = stream.ConsumeRemainingBytesAsString();
  const int w = stream.ConsumeIntegral<int>();
  const int h = stream.ConsumeIntegral<int>();
  const int colortype = stream.ConsumeIntegral<int>();
  const int bitdepth = stream.ConsumeIntegral<int>();
  lodepng_encode_file(filename.c_str(), image.c_str(), w, h, colortype, bitdepth);
  return 0;
}