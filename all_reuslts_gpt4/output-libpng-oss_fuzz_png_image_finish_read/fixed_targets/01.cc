#include <fuzzer/FuzzedDataProvider.h>
#include <cstddef>
#include <cstdint>
#include <vector>

#include "png.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  
  // Initialize a png_image struct
  png_image image;
  image.version = PNG_IMAGE_VERSION;
  image.width = stream.ConsumeIntegral<uint32_t>();
  image.height = stream.ConsumeIntegral<uint32_t>();
  image.format = stream.ConsumeIntegral<uint32_t>();
  image.flags = stream.ConsumeIntegral<uint32_t>();
  image.colormap_entries = stream.ConsumeIntegral<uint32_t>();
  image.warning_or_error = stream.ConsumeIntegral<int>();
  image.message[0] = '\0';

  // Initialize a png_color_struct
  png_color_struct background;
  background.red = stream.ConsumeIntegral<uint8_t>();
  background.green = stream.ConsumeIntegral<uint8_t>();
  background.blue = stream.ConsumeIntegral<uint8_t>();

  // Initialize a buffer
  size_t buffer_size = stream.ConsumeIntegralInRange<size_t>(0, 4096);
  std::vector<char> buffer(buffer_size);

  // Initialize row_stride
  int row_stride = stream.ConsumeIntegral<int>();

  // Initialize colormap
  size_t colormap_size = stream.ConsumeIntegralInRange<size_t>(0, 4096);
  std::vector<char> colormap(colormap_size);

  // Call the function to fuzz
  OSS_FUZZ_png_image_finish_read(&image, &background, buffer.data(), row_stride, colormap.data());

  return 0;
}