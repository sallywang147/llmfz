#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include <fuzzer/FuzzedDataProvider.h>

extern "C" {
#include <vulkan/vulkan.h>
}

typedef PFN_vkVoidFunction func_type;

int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider stream(data, size);

  // Extract a device.
  uint64_t device = stream.ConsumeIntegral<uint64_t>();

  // Extract a string.
  std::string str = stream.ConsumeRandomLengthString();
  char *ptr = str.c_str();

  // Call the function.
  func_type *ret = vkGetDeviceProcAddr((VkDevice)device, ptr);

  if (ret == nullptr) {
    // Handle the case where the function is not found.
    // For example, log the error or return an error code.
    fprintf(stderr, "Function not found: %s\n", ptr);
    return 1;
  }

  return 0;
}