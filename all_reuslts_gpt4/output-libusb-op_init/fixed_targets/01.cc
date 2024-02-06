#include <fuzzer/FuzzedDataProvider.h>
#include <libusb.h>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  struct libusb_context *ctx = nullptr;
  int ret = libusb_init(&ctx);
  if (ret < 0) {
    return 0; // Cannot initialize libusb.
  }

  FuzzedDataProvider stream(data, size);
  if (stream.ConsumeBool()) {
    libusb_set_debug(ctx, LIBUSB_LOG_LEVEL_INFO);
  } else {
    libusb_set_debug(ctx, LIBUSB_LOG_LEVEL_WARNING);
  }

  op_init(ctx);

  libusb_exit(ctx);
  return 0;
}