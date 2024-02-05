#include <fuzzer/FuzzedDataProvider.h>
#include <libusb-1.0/libusb.h>
#include <cstdint>
#include <cstddef>
#include <vector>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider stream(data, size);

  // Initialize libusb
  libusb_context *context = NULL;
  if (libusb_init(&context) < 0) {
    return 0;
  }

  // Open a device
  libusb_device_handle *dev_handle = libusb_open_device_with_vid_pid(context, 0x04d8, 0x003f);
  if (dev_handle == NULL) {
    libusb_exit(context);
    return 0;
  }

  // Get the descriptor index
  char desc_index = stream.ConsumeIntegral<char>();

  // Get the length and data
  int length = stream.ConsumeIntegralInRange<int>(0, 256);
  std::vector<char> data(length);

  // Call the function to fuzz
  libusb_get_string_descriptor_ascii(dev_handle, desc_index, data.data(), length);

  // Clean up
  libusb_close(dev_handle);
  libusb_exit(context);

  return 0;
}