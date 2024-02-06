#include <fuzzer/FuzzedDataProvider.h>
#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <libusb.h>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider stream(data, size);

  // Initialize libusb
  libusb_context *ctx = NULL;
  if (libusb_init(&ctx) < 0) {
    return 0; // Failed to initialize libusb
  }

  // Open a device
  libusb_device_handle *dev_handle = libusb_open_device_with_vid_pid(ctx, 0x04b3, 0x3108);
  if (dev_handle == NULL) {
    libusb_exit(ctx);
    return 0; // Failed to open device
  }

  // Extract parameters for libusb_get_string_descriptor
  char desc_index = stream.ConsumeIntegral<char>();
  short langid = stream.ConsumeIntegral<short>();
  int length = stream.ConsumeIntegralInRange<int>(0, 256);
  std::vector<char> data(length);

  // Call the target function
  libusb_get_string_descriptor(dev_handle, desc_index, langid, data.data(), length);

  // Cleanup
  libusb_close(dev_handle);
  libusb_exit(ctx);

  return 0;
}