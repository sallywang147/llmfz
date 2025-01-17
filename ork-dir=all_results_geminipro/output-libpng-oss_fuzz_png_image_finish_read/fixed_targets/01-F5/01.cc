#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <cstring>
#include <vector>

#include "png.h"

extern "C" {
int OSS_FUZZ_png_image_finish_read(png_image* image, png_color_struct* background, char* buffer, int row_stride, char* colormap);
void png_image_free(png_image* image);
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  png_image image;
  memset(&image, 0, sizeof(image));
  image.version = PNG_IMAGE_VERSION;

  const uint32_t width = stream.ConsumeIntegral<uint32_t>();
  const uint32_t height = stream.ConsumeIntegral<uint32_t>();
  const uint8_t bit_depth = stream.ConsumeIntegralInRange<uint8_t>(1, 16);
  const uint8_t color_type = stream.ConsumeIntegralInRange<uint8_t>(0, 6);
  const uint8_t interlace_type = stream.ConsumeIntegralInRange<uint8_t>(0, 1);
  const uint8_t compression_type = stream.ConsumeIntegralInRange<uint8_t>(0, 1);
  const uint8_t filter_type = stream.ConsumeIntegralInRange<uint8_t>(0, 5);

  image.width = width;
  image.height = height;
  image.bit_depth = bit_depth;
  image.color_type = color_type;
  image.interlace_type = interlace_type;
  image.compression_type = compression_type;
  image.filter_type = filter_type;

  const size_t buffer_size = width * height * (bit_depth / 8);
  std::vector<uint8_t> buffer(buffer_size);
  stream.ConsumeBytes<uint8_t>(buffer.data(), buffer_size);
  image.buffer = buffer.data();

  png_color_struct background;
  memset(&background, 0, sizeof(background));
  background.red = stream.ConsumeIntegral<uint8_t>();
  background.green = stream.ConsumeIntegral<uint8_t>();
  background.blue = stream.ConsumeIntegral<uint8_t>();

  int row_stride = stream.ConsumeIntegral<int>();
  std::vector<uint8_t> colormap(768);
  stream.ConsumeBytes<uint8_t>(colormap.data(), 768);

  int result = OSS_FUZZ_png_image_finish_read(&image, &background,
                                            reinterpret_cast<char*>(buffer.data()),
                                            row_stride,
                                            reinterpret_cast<char*>(colormap.data()));
  if (result != 0) {
    return 0;
  }

  png_image_free(&image);
  return 0;
}