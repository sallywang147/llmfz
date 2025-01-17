#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>

#include "libusb.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  // Initialize the library
  libusb_context *ctx = NULL;
  if (libusb_init(&ctx) < 0) {
    return 0;
  }

  // Open a device
  libusb_device_handle *dev_handle = libusb_open_device_with_vid_pid(ctx, 0x04b3, 0x3108);
  if (dev_handle == NULL) {
    libusb_exit(ctx);
    return 0;
  }

  // Consume data from the fuzzer input
  char desc_index = stream.ConsumeIntegral<char>();
  short langid = stream.ConsumeIntegral<short>();
  int length = stream.ConsumeIntegralInRange<int>(0, 255);
  std::vector<char> data_vector(length);
  char* data = data_vector.data();

  // Call the function to be fuzzed
  libusb_get_string_descriptor(dev_handle, desc_index, langid, data, length);

  // Clean up
  libusb_close(dev_handle);
  libusb_exit(ctx);

  return 0;
}