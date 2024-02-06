#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "png.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  // Initialize the image structure
  struct png_image image;
  memset(&image, 0, sizeof(image));
  image.version = PNG_IMAGE_VERSION;

  // Consume the remaining bytes as a string
  std::string memory = stream.ConsumeRemainingBytesAsString();

  // Call the target function
  int result = OSS_FUZZ_png_image_begin_read_from_memory(&image, const_cast<char*>(memory.c_str()), memory.size());

  // Free any memory that may have been allocated
  png_image_free(&image);

  return 0;
}