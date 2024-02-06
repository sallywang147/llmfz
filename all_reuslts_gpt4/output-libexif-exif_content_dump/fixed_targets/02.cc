#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>

#include "libexif/exif-content.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  // Create a new ExifContent object
  ExifContent *content = exif_content_new();
  if (!content) {
    return 0;
  }

  // Initialize the ExifContent object with random data
  size_t consumed = stream.ConsumeData(content, sizeof(*content));

  // Consume an integer for the indent parameter
  int indent = stream.ConsumeIntegral<int>();

  // Call the target function
  exif_content_dump(content, indent);

  // Clean up
  exif_content_unref(content);

  return 0;
}