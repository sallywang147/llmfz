#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include "fuzzer/FuzzedDataProvider.h"
#include "vulkan/vulkan.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider stream(data, size);

  // Extract integral values
  int layer_count = stream.ConsumeIntegral<int>();

  VkLayerProperties* layer_properties = NULL;
  if (stream.remaining_bytes() > 0) {
    layer_properties = new VkLayerProperties();
  }

  int result = vkEnumerateInstanceLayerProperties(&layer_count, layer_properties);

  delete layer_properties;

  return 0;
}