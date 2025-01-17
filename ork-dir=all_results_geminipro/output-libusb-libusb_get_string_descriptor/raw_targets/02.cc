#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>

#include "libusb/libusb.h"
#include "libusb/libusbi.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  struct libusb_device_handle *dev_handle = NULL;
  FuzzedDataProvider stream(data, size);
  char desc_index = stream.ConsumeIntegral<char>();
  short langid = stream.ConsumeIntegral<short>();
  int length = stream.ConsumeIntegralInRange<int>(0, 1024);
  std::string input = stream.ConsumeRandomLengthString();
  const char *d = input.c_str();

  int ret = libusb_get_string_descriptor(dev_handle, desc_index, langid, (char *)d, length);

  return ret;
}