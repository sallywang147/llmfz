#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>

#include "libusb/libusb.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  struct libusb_device_handle *handle = nullptr;
  int configuration = 0;
  FuzzedDataProvider stream(data, size);
  int ret = libusb_get_device_list(nullptr, &handle);
  if (ret < 0) {
    return 0;
  }
  libusb_free_device_list(handle, 1);

  ret = libusb_init(nullptr);
  if (ret < 0) {
    return 0;
  }

  ret = libusb_open(handle, &handle);
  if (ret < 0) {
    libusb_exit(nullptr);
    return 0;
  }

  libusb_get_configuration(handle, &configuration);

  libusb_close(handle);
  libusb_exit(nullptr);
  return 0;
}