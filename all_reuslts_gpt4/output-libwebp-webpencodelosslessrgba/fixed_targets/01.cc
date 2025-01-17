#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <vector>

#include "webp/encode.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  const int width = stream.ConsumeIntegralInRange<int>(1, 4096);
  const int height = stream.ConsumeIntegralInRange<int>(1, 4096);
  const int bytes_per_pixel = stream.ConsumeIntegralInRange<int>(1, 4);
  const size_t total_size = static_cast<size_t>(width) * height * bytes_per_pixel;

  if (total_size > stream.remaining_bytes()) {
    return 0;
  }

  std::vector<char> image_data = stream.ConsumeBytes<char>(total_size);
  char* output_data = nullptr;

  WebPEncodeLosslessRGBA(image_data.data(), width, height, bytes_per_pixel, &output_data);

  if (output_data != nullptr) {
    free(output_data);
  }

  return 0;
}