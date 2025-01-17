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
  int config = stream.ConsumeIntegral<int>();
  struct libusb_device_handle *dev_handle = NULL;

  libusb_get_configuration(dev_handle, &config);

  return 0;
}