#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <vector>

#include "png.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  if (size == 0) {
    return 0;
  }

  FuzzedDataProvider stream(data, size);

  // Initialize the png structures
  png_structp png_ptr = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
  if (!png_ptr) {
    return 0;
  }

  png_infop info_ptr = png_create_info_struct(png_ptr);
  if (!info_ptr) {
    png_destroy_read_struct(&png_ptr, NULL, NULL);
    return 0;
  }

  // Set error handling
  if (setjmp(png_jmpbuf(png_ptr))) {
    png_destroy_read_struct(&png_ptr, &info_ptr, NULL);
    return 0;
  }

  // Initialize the png reading
  png_set_read_fn(png_ptr, NULL, NULL);

  // Extract parameters
  int transforms = stream.ConsumeIntegral<int>();
  std::string params_str = stream.ConsumeRemainingBytesAsString();
  char* params = const_cast<char*>(params_str.c_str());

  // Call the function to fuzz
  OSS_FUZZ_png_read_png(png_ptr, info_ptr, transforms, params);

  // Cleanup
  png_destroy_read_struct(&png_ptr, &info_ptr, NULL);

  return 0;
}