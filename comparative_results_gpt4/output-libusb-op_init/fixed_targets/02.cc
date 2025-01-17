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

  libusb_context* ctx;
  int ret = libusb_init(&ctx);
  if (ret < 0) {
    return 0;
  }

  // Call the function to fuzz
  op_init(ctx);

  libusb_exit(ctx);

  return 0;
}