#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "libexif/exif-data.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  if (size < 1) {
    return 0;
  }

  FuzzedDataProvider provider(data, size);

  // Create a new ExifData object
  ExifData* exifData = exif_data_new();
  if (exifData == nullptr) {
    return 0;
  }

  // Get byte order from the fuzzer
  ExifByteOrder byteOrder = static_cast<ExifByteOrder>(provider.ConsumeIntegralInRange<int>(0, 1));

  // Set byte order
  exif_data_set_byte_order(exifData, byteOrder);

  // Clean up
  exif_data_unref(exifData);

  return 0;
}