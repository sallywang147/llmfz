#include <libexif/exif-data.h>
#include <stddef.h>
#include <stdlib.h>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {

  // Parse tags using (ultimately) exif_data_load_data()
  auto image = exif_data_new_from_data(data, size);
  if (image) {
    // Exercise the EXIF tag manipulation code
    exif_data_set_byte_order(image, EXIF_BYTE_ORDER_INTEL);
    exif_data_set_byte_order(image, EXIF_BYTE_ORDER_MOTOROLA);
    exif_data_unref(image);
  }

  return 0;
}