#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>

extern "C" {
#include "libusb/libusb.h"
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  struct libusb_device_handle *dev_handle = nullptr;
  FuzzedDataProvider stream(data, size);
  char desc_index = stream.ConsumeIntegral<char>();
  short langid = stream.ConsumeIntegral<short>();
  char *data_ptr = new char[size];
  int length = stream.ConsumeIntegralInRange<int>(0, size);

  int ret = libusb_get_string_descriptor(dev_handle, desc_index, langid, data_ptr, length);

  delete[] data_ptr;
  return ret;
}