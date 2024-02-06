#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <vector>

#include "png.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  if (size < sizeof(png_image))
    return 0;

  FuzzedDataProvider stream(data, size);

  // Extracting image
  png_image image;
  stream.ConsumeData(&image, sizeof(image));

  // Extracting background
  png_color_struct background;
  stream.ConsumeData(&background, sizeof(background));

  // Extracting row_stride
  int row_stride = stream.ConsumeIntegral<int>();

  // Extracting buffer
  std::vector<char> buffer = stream.ConsumeRemainingBytes<char>();

  // Extracting colormap
  std::vector<char> colormap = stream.ConsumeBytes<char>(stream.remaining_bytes());

  // Call the target function
  OSS_FUZZ_png_image_finish_read(&image, &background, buffer.data(), row_stride, colormap.data());

  return 0;
}