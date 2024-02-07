#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "libusb.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  static bool initialized = false;
  if (!initialized) {
    libusb_init(nullptr);
    initialized = true;
  }

  struct libusb_context *ctx = nullptr;
  int ret = libusb_init(&ctx);
  if (ret != 0 || ctx == nullptr) {
    return 0;
  }

  op_init(ctx);

  libusb_exit(ctx);

  return 0;
}