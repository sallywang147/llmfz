#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>

#include "libusb.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  struct libusb_context *ctx = NULL;
  int ret;

  // Initialize libusb context
  ret = libusb_init(&ctx);
  if (ret != LIBUSB_SUCCESS) {
    return 0;
  }

  // Call the target function
  ret = op_init(ctx);

  // Deinitialize libusb context
  libusb_exit(ctx);

  return 0;
}