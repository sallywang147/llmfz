#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>

extern "C" {
#include "libusb/libusb.h"
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  struct libusb_context *ctx = NULL;
  FuzzedDataProvider stream(data, size);
  int ret = libusb_init(&ctx);
  if (ret < 0) {
    return ret;
  }

  ret = op_init(ctx);
  if (ret < 0) {
    return ret;
  }

  libusb_exit(ctx);
  return 0;
}