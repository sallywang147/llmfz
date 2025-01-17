#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>

#include <fuzzer/FuzzedDataProvider.h>

extern "C" {
#include <vulkan/vulkan.h>
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider stream(data, size);

  // Extract an array of bytes as a vector. You MUST call .data() to use result as pointer.
  std::vector<uint8_t> bytes = stream.ConsumeBytes<uint8_t>(stream.ConsumeIntegralInRange(0, 1024));
  char *ptr = reinterpret_cast<char *>(bytes.data());

  // Extract an array of bytes as a vector. You MUST call .data() to use result as pointer.
  std::vector<uint8_t> bytes2 = stream.ConsumeBytes<uint8_t>(stream.ConsumeIntegralInRange(0, 1024));
  char *ptr2 = reinterpret_cast<char *>(bytes2.data());

  VkDevice device = reinterpret_cast<VkDevice>(ptr);
  vkGetDeviceProcAddr(device, ptr2);

  return 0;
}