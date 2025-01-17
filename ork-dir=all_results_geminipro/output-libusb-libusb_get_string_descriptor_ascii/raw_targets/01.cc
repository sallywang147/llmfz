#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <string>

#include "libusb/libusb.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  struct libusb_device_handle *handle = nullptr;
  FuzzedDataProvider stream(data, size);
  char desc_index = stream.ConsumeIntegral<char>();
  int length = stream.ConsumeIntegral<int>();
  std::string input = stream.ConsumeRandomLengthString();
  const char *d = input.c_str();

  libusb_get_string_descriptor_ascii(handle, desc_index, (char *)d, length);

  return 0;
}