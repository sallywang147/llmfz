#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <string>

#include "lodepng.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider stream(data, size);
  const std::string filename = stream.ConsumeRemainingBytesAsString();
  const std::vector<uint8_t> image = stream.ConsumeRemainingBytes();
  const uint32_t w = stream.ConsumeIntegral<uint32_t>();
  const uint32_t h = stream.ConsumeIntegral<uint32_t>();

  lodepng_encode32_file(filename.c_str(), reinterpret_cast<char*>(image.data()), w, h);
  return 0;
}