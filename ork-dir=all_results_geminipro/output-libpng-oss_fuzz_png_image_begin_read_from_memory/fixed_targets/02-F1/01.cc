#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <cstring>
#include <png.h>

extern "C" {
#include <libpng16/png.h>
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  struct png_image image;
  memset(&image, 0, sizeof(image));
  image.version = PNG_IMAGE_VERSION;

  const size_t memory_size = stream.ConsumeIntegral<size_t>();
  char* memory = new char[memory_size];
  stream.ConsumeBytes<char>(memory, memory_size);

  int result = OSS_FUZZ_png_image_begin_read_from_memory(&image, memory,
                                                       memory_size);
  if (result != 0) {
    return 0;
  }

  OSS_FUZZ_png_image_free(&image);
  delete[] memory;
  return 0;
}