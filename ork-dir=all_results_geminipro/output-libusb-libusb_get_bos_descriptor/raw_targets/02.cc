#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>

#include "libusb/libusb.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  struct libusb_device_handle *dev_handle = NULL;
  struct libusb_bos_descriptor *bos = NULL;
  FuzzedDataProvider stream(data, size);
  int ret;

  ret = libusb_get_device_descriptor(NULL, NULL);
  if (ret != LIBUSB_SUCCESS) {
    return ret;
  }

  ret = libusb_get_bos_descriptor(dev_handle, &bos);
  if (ret != LIBUSB_SUCCESS) {
    return ret;
  }

  libusb_free_bos_descriptor(bos);

  return 0;
}