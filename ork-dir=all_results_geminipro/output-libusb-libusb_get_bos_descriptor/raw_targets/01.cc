#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>

#include "libusb/libusb.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  struct libusb_device_handle *dev_handle = nullptr;
  struct libusb_bos_descriptor *bos = nullptr;

  FuzzedDataProvider stream(data, size);
  uint8_t bmRequestType = stream.ConsumeIntegral<uint8_t>();
  uint8_t bRequest = stream.ConsumeIntegral<uint8_t>();
  uint16_t wValue = stream.ConsumeIntegral<uint16_t>();
  uint16_t wIndex = stream.ConsumeIntegral<uint16_t>();
  uint16_t wLength = stream.ConsumeIntegral<uint16_t>();
  std::string input = stream.ConsumeRandomLengthString();
  const char *d = input.c_str();

  libusb_fill_control_setup((unsigned char *)d, bmRequestType, bRequest, wValue, wIndex, wLength);

  int ret = libusb_get_bos_descriptor(dev_handle, &bos);
  if (ret == LIBUSB_SUCCESS) {
    libusb_free_bos_descriptor(bos);
  }

  return 0;
}