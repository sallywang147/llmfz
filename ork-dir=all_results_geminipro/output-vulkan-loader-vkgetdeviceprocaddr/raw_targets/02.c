#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include <fuzzer/FuzzedDataProvider.h>

int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider stream(data, size);

  // Extract a device.
  uint64_t device = stream.ConsumeIntegral<uint64_t>();

  // Extract a string.
  std::string str = stream.ConsumeRandomLengthString();
  char *ptr = str.c_str();

  // Call the function.
  func_type *ret = vkGetDeviceProcAddr((struct VkDevice_T *)device, ptr);

  return 0;
}