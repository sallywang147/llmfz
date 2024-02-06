#include <fuzzer/FuzzedDataProvider.h>
#include <libexif/exif-data.h>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider stream(data, size);

  // Initialize exif data
  ExifData *exif_data = exif_data_new();
  if (!exif_data) {
    return 0;
  }

  // Consume data for order from the input stream
  int order = stream.ConsumeIntegral<int>();

  // Call the target function
  exif_data_set_byte_order(exif_data, order);

  // Cleanup
  exif_data_unref(exif_data);

  return 0;
}