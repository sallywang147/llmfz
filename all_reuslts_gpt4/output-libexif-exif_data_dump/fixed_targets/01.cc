#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "libexif/exif-data.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  // Create an ExifData object
  ExifData *exif_data = exif_data_new();
  if (!exif_data) {
    return 0;
  }

  // Load data into the ExifData object
  exif_data_load_data(exif_data, stream.ConsumeRemainingBytes<uint8_t>().data(), size);

  // Call the function to be fuzzed
  exif_data_dump(exif_data);

  // Clean up and return
  exif_data_unref(exif_data);
  return 0;
}