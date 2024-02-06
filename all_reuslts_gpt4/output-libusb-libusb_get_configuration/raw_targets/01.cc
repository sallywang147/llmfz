#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "libusb.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  static bool initialized = false;
  if (!initialized) {
    libusb_init(NULL);
    initialized = true;
  }

  FuzzedDataProvider stream(data, size);

  struct libusb_device_handle *dev_handle;
  int config;
  int ret;

  // Open a device handle
  ret = libusb_open(NULL, &dev_handle);
  if (ret != 0) {
    return 0;
  }

  // Call the function under test
  ret = libusb_get_configuration(dev_handle, &config);

  // Close the device handle
  libusb_close(dev_handle);

  return 0;
}