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

  // Get a list of devices
  libusb_device **devs;
  ssize_t cnt = libusb_get_device_list(NULL, &devs);
  if (cnt < 0) {
    return 0;
  }

  // Choose a random device from the list
  libusb_device *dev = devs[stream.ConsumeIntegralInRange<size_t>(0, cnt - 1)];

  libusb_device_handle *dev_handle;
  // Open the device
  int r = libusb_open(dev, &dev_handle);
  if (r < 0) {
    libusb_free_device_list(devs, 1);
    return 0;
  }

  // Define and initialize parameters for the function
  char desc_index = stream.ConsumeIntegral<char>();
  int length = stream.ConsumeIntegralInRange<int>(1, 256); // Length must be > 0
  std::vector<char> data(length);

  // Call the function to fuzz
  libusb_get_string_descriptor_ascii(dev_handle, desc_index, data.data(), length);

  // Clean up
  libusb_close(dev_handle);
  libusb_free_device_list(devs, 1);

  return 0;
}