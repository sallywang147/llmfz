#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "vulkan/vulkan.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider provider(data, size);
  int layer_count = provider.ConsumeIntegral<int>();
  if (layer_count < 0) {
    return 0;
  }
  std::vector<VkLayerProperties> layer_properties(layer_count);
  int ret = vkEnumerateInstanceLayerProperties(&layer_count,
                                             layer_properties.data());
  if (ret != VK_SUCCESS) {
    return 0;
  }
  return 0;
}