#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "libusb.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  libusb_context *ctx = NULL;
  int ret;

  // Initialize the library. This must be called before calling any other libusb function.
  if (libusb_init(&ctx) < 0) {
    return 0;
  }

  // Set the debug level to 0, no messages are ever printed.
  libusb_set_debug(ctx, 0);

  // Call the target function
  ret = op_init(ctx);

  // Deinitialize the library
  libusb_exit(ctx);

  return 0;
}