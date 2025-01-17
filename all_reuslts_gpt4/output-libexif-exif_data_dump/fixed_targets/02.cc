#include <fuzzer/FuzzedDataProvider.h>
#include <libexif/exif-data.h>
#include <cstddef>
#include <cstdint>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider stream(data, size);
  ExifData *exifData = exif_data_new();

  if (exifData == nullptr) {
    return 0;
  }

  // Consume all remaining bytes
  std::vector<uint8_t> bytes = stream.ConsumeRemainingBytes<uint8_t>();

  // Use the consumed bytes to load the EXIF data
  exif_data_load_data(exifData, bytes.data(), bytes.size());

  // Dump the EXIF data
  exif_data_dump(exifData);

  // Free the EXIF data
  exif_data_unref(exifData);

  return 0;
}