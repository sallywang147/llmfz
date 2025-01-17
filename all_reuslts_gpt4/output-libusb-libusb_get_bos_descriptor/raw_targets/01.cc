#include <fuzzer/FuzzedDataProvider.h>
#include <libusb.h>
#include <stdint.h>
#include <stdlib.h>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  static bool initialized = false;
  if (!initialized) {
    libusb_init(NULL);
    initialized = true;
  }

  FuzzedDataProvider stream(data, size);

  // Create a fake device handle to pass to libusb_get_bos_descriptor.
  libusb_device_handle *dev_handle = reinterpret_cast<libusb_device_handle*>(1);

  // Initialize a libusb_bos_descriptor pointer.
  struct libusb_bos_descriptor *bos = NULL;

  // Call the function under test.
  libusb_get_bos_descriptor(dev_handle, &bos);

  // Free the bos descriptor if it was successfully retrieved.
  if (bos != NULL) {
    libusb_free_bos_descriptor(bos);
  }

  return 0;
}