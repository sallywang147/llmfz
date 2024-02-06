#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>

extern "C" {
#include "libusb/libusb.h"
}

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
```

The issue was that the `libusb.h` header was not wrapped with `extern "C" {}`. This is necessary when using C libraries in C++ code to ensure that the function names are not mangled. Wrapping the header with `extern "C" {}` tells the compiler to use the C calling convention for the functions declared in the header.

The corrected code includes the `extern "C" {}` wrapper around the `libusb.h` header, which should resolve the build error.