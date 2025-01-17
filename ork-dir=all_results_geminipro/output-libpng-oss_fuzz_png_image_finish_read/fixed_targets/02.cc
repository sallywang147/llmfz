#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

extern "C" {
#include "png.h"
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  const uint8_t width = stream.ConsumeIntegral<uint8_t>();
  const uint8_t height = stream.ConsumeIntegral<uint8_t>();
  const uint8_t bit_depth = stream.ConsumeIntegral<uint8_t>();
  const uint8_t color_type = stream.ConsumeIntegral<uint8_t>();
  const uint8_t interlace_type = stream.ConsumeIntegral<uint8_t>();
  const uint8_t compression_type = stream.ConsumeIntegral<uint8_t>();
  const uint8_t filter_type = stream.ConsumeIntegral<uint8_t>();

  png_image image;
  memset(&image, 0, sizeof(image));
  image.version = PNG_IMAGE_VERSION;
  image.width = width;
  image.height = height;
  image.bit_depth = bit_depth;
  image.color_type = color_type;
  image.interlace_type = interlace_type;
  image.compression_type = compression_type;
  image.filter_type = filter_type;

  const size_t row_stride = width * (bit_depth + 7) / 8;
  std::vector<uint8_t> buffer(row_stride * height);
  png_color_struct background;
  memset(&background, 0, sizeof(background));

  const auto input = stream.ConsumeRemainingBytes();
  int ret = OSS_FUZZ_png_image_finish_read(&image, &background,
                                          reinterpret_cast<char*>(buffer.data()),
                                          row_stride, nullptr);
  if (ret != 0) {
    fprintf(stderr, "OSS_FUZZ_png_image_finish_read returned %d\n", ret);
    abort();
  }
  return 0;
}