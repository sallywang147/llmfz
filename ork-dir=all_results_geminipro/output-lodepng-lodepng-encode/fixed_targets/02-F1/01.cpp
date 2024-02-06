#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <string>

#include "lodepng.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  const std::string filename = stream.ConsumeRemainingBytesAsString();
  const int w = stream.ConsumeIntegral<int>();
  const int h = stream.ConsumeIntegral<int>();
  const int colortype = stream.ConsumeIntegral<int>();
  const int bitdepth = stream.ConsumeIntegral<int>();
  const std::string image_data = stream.ConsumeRemainingBytesAsString();

  std::vector<unsigned char> png;
  int error = lodepng::encode(png, image_data.c_str(), w, h, colortype, bitdepth);
  if (error != 0) {
    return 0;
  }
  std::ofstream file(filename, std::ios::out | std::ios::binary);
  file.write((char*)png.data(), png.size());
  file.close();
  return 0;
}