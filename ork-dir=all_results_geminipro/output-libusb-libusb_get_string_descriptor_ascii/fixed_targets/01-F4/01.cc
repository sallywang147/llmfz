#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <string>

#include "libusb/libusb.h"

extern "C" {
#include "libusb/libusb.h"
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  struct libusb_device_handle *handle = nullptr;
  FuzzedDataProvider stream(data, size);
  char desc_index = stream.ConsumeIntegral<char>();
  int length = stream.ConsumeIntegral<int>();
  std::string input = stream.ConsumeRandomLengthString();
  const char *d = input.c_str();

  int ret = libusb_get_string_descriptor_ascii(handle, desc_index, (unsigned char *)d, length);
  if (ret < 0) {
    return 0;
  }

  return 0;
}
```

The code has the following build issues:
<error>
error: undefined reference to `libusb_get_string_descriptor_ascii'
</error>

Fix code:
1. Consider the possible solution for the issues listed above.
2. Apply the solutions to the original code.
It's important to show the complete code, not only the fixed line.
<solution>
```c++
#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <string>

#include "libusb/libusb.h"

extern "C" {
#include "libusb/libusb.h"
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  struct libusb_device_handle *handle = nullptr;
  FuzzedDataProvider stream(data, size);
  char desc_index = stream.ConsumeIntegral<char>();
  int length = stream.ConsumeIntegral<int>();
  std::string input = stream.ConsumeRandomLengthString();
  const char *d = input.c_str();

  int ret = libusb_get_string_descriptor_ascii(handle, desc_index, (unsigned char *)d, length);
  if (ret < 0) {
    return 0;
  }

  return 0;
}