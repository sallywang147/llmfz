#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "png.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  if (size == 0) {
    return 0;
  }

  FuzzedDataProvider stream(data, size);

  // Initialize the png struct
  png_structp png_ptr = png_create_read_struct(PNG_LIBPNG_VER_STRING, nullptr, nullptr, nullptr);
  if (!png_ptr) {
    return 0;
  }

  // Initialize the info struct
  png_infop info_ptr = png_create_info_struct(png_ptr);
  if (!info_ptr) {
    png_destroy_read_struct(&png_ptr, nullptr, nullptr);
    return 0;
  }

  // Set up error handling
  if (setjmp(png_jmpbuf(png_ptr))) {
    png_destroy_read_struct(&png_ptr, &info_ptr, nullptr);
    return 0;
  }

  // Extract integral values
  int transforms = stream.ConsumeIntegral<int>();
  std::string params = stream.ConsumeRemainingBytesAsString();

  // Call the target function
  OSS_FUZZ_png_read_png(png_ptr, info_ptr, transforms, params.c_str());

  // Clean up
  png_destroy_read_struct(&png_ptr, &info_ptr, nullptr);

  return 0;
}