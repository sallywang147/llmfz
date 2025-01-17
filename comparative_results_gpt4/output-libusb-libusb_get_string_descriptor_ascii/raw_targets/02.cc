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
  
  FuzzedDataProvider stream(data, size);

  // Mock device handle, as we can't generate a valid one.
  libusb_device_handle *dev_handle = nullptr;

  // Generate parameters for the function call.
  char desc_index = stream.ConsumeIntegral<char>();
  int length = stream.ConsumeIntegral<int>();
  std::vector<char> data_vector = stream.ConsumeBytes<char>(length);
  char *data = data_vector.data();

  // Call the function with the generated parameters.
  libusb_get_string_descriptor_ascii(dev_handle, desc_index, data, length);

  return 0;
}