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
    libusb_init(NULL);
    initialized = true;
  }

  FuzzedDataProvider stream(data, size);

  // We need a valid libusb_device_handle. Since we can't create one, we use NULL.
  // This will limit the paths we can reach in the fuzzed function, but there is no other option.
  struct libusb_device_handle *dev_handle = NULL;

  // Consume a byte for the descriptor index.
  char desc_index = stream.ConsumeIntegral<char>();

  // Consume the remaining bytes for the data buffer.
  std::vector<char> data_buffer = stream.ConsumeRemainingBytes<char>();

  // Call the function with the fuzzed input.
  libusb_get_string_descriptor_ascii(dev_handle, desc_index, data_buffer.data(), data_buffer.size());

  return 0;
}