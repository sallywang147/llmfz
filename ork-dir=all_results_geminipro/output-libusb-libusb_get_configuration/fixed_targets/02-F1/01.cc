#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>

extern "C" {
#include "libusb/libusb.h"
}

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
```
The fix is to wrap the `#include "libusb/libusb.h"` directive with `extern "C" {}`. This is necessary because the libusb library is written in C, and the C++ compiler needs to be told to use the C calling convention when calling the libusb functions.