#include <fuzzer/FuzzedDataProvider.h>
#include <cstdint>
#include <string>
#include <vector>

extern "C" {
#include "lodepng.h"
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider stream(data, size);

  const std::string filename = stream.ConsumeRandomLengthString();
  const std::vector<uint8_t> image = stream.ConsumeRemainingBytes<uint8_t>();
  const int w = stream.ConsumeIntegral<int>();
  const int h = stream.ConsumeIntegral<int>();
  const int colortype = stream.ConsumeIntegral<int>();
  const int bitdepth = stream.ConsumeIntegral<int>();

  lodepng::encode(filename, reinterpret_cast<char *>(image.data()), w, h, colortype,
                 bitdepth);
  return 0;
}