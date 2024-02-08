#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstring>
#include <string>

#include "libusb/libusb.h"
#include "libusb/libusbi.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider stream(data, size);
  libusb_device_handle *dev_handle = NULL;
  char desc_index = stream.ConsumeIntegral<char>();
  int length = stream.ConsumeIntegralInRange<int>(1, 1024);
  std::string input = stream.ConsumeRandomLengthString();
  const char *d = input.c_str();

  int ret = libusb_get_string_descriptor_ascii(dev_handle, desc_index, (char *)d, length);
  if (ret < 0) {
    return ret;
  }

  return 0;
}