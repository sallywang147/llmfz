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

  libusb_device_handle *dev_handle;
  libusb_bos_descriptor *bos;

  // Open a device
  dev_handle = libusb_open_device_with_vid_pid(NULL, 0x04b3, 0x3108);
  if(dev_handle == NULL) {
    return 0;
  }

  FuzzedDataProvider stream(data, size);
  if (stream.remaining_bytes() > 0) {
    std::vector<uint8_t> buffer = stream.ConsumeRemainingBytes<uint8_t>();
    libusb_control_transfer(dev_handle, 0x80, 0x06, 0x1d00, 0, buffer.data(), buffer.size(), 5000);
  }

  // Call the target function
  libusb_get_bos_descriptor(dev_handle, &bos);

  // Clean up
  libusb_free_bos_descriptor(bos);
  libusb_close(dev_handle);

  return 0;
}