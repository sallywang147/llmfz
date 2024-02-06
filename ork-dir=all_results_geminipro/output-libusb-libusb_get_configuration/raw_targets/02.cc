#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>

#include "libusb/libusb.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  struct libusb_device_handle *dev_handle = NULL;
  int config = 0;
  FuzzedDataProvider stream(data, size);
  uint8_t bus_number = stream.ConsumeIntegral<uint8_t>();
  uint8_t device_address = stream.ConsumeIntegral<uint8_t>();

  libusb_init(NULL);
  dev_handle = libusb_open_device_with_vid_pid(NULL, bus_number, device_address);
  if (!dev_handle) {
    return 0;
  }

  libusb_get_configuration(dev_handle, &config);

  libusb_close(dev_handle);
  libusb_exit(NULL);

  return 0;
}