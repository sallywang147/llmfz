#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstring>
#include <string>

extern "C" {
#include "libusb/libusb.h"
#include "libusb/libusbi.h"
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider stream(data, size);
  libusb_context *ctx = NULL;
  libusb_device_handle *dev_handle = NULL;
  char desc_index = stream.ConsumeIntegral<char>();
  int length = stream.ConsumeIntegralInRange<int>(1, 1024);
  std::string input = stream.ConsumeRandomLengthString();
  char *d = new char[length + 1];
  memset(d, 0, length + 1);
  strcpy(d, input.c_str());

  int ret = libusb_init(&ctx);
  if (ret < 0) {
    return ret;
  }

  ret = libusb_get_device_list(ctx, &dev_handle);
  if (ret < 0) {
    return ret;
  }

  ret = libusb_get_string_descriptor_ascii(dev_handle, desc_index, (unsigned char *)d, length);
  if (ret < 0) {
    return ret;
  }

  libusb_free_device_list(dev_handle, 1);
  libusb_exit(ctx);

  delete[] d;

  return 0;
}