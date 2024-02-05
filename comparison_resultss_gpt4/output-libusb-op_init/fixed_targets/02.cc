#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "libusb.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  struct libusb_context *ctx = NULL;
  int ret = libusb_init(&ctx);
  if (ret < 0) {
    return 0;
  }

  FuzzedDataProvider provider(data, size);
  op_init(ctx);

  libusb_exit(ctx);
  return 0;
}