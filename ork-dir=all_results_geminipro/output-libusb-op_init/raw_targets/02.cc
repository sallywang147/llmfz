#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>

#include "libusb/libusb.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider stream(data, size);
  struct libusb_context *ctx = NULL;
  int ret;

  ret = libusb_init(&ctx);
  if (ret != 0) {
    return ret;
  }

  ret = op_init(ctx);
  if (ret != 0) {
    libusb_exit(ctx);
    return ret;
  }

  libusb_exit(ctx);
  return 0;
}