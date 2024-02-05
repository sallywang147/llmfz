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

  FuzzedDataProvider provider(data, size);
  
  // Assuming we have a valid device handle. In a real-world scenario, this would be obtained by opening a USB device with libusb.
  struct libusb_device_handle *dev_handle = NULL; 

  char desc_index = provider.ConsumeIntegral<char>();
  int length = provider.ConsumeIntegral<int>();
  std::vector<char> data(length);

  int ret = libusb_get_string_descriptor_ascii(dev_handle, desc_index, data.data(), length);

  return 0;
}