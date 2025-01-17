#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include <fuzzer/FuzzedDataProvider.h>

#include "loader.h"

int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider stream(data, size);

  VkEnumerateInstanceLayerPropertiesChain chain = {
      .sType = VK_STRUCTURE_TYPE_ENUMERATE_INSTANCE_LAYER_PROPERTIES_CHAIN,
      .pNext = NULL,
  };
  int property_count = stream.ConsumeIntegral<int>();
  VkLayerProperties *properties =
      (VkLayerProperties *)malloc(sizeof(VkLayerProperties) * property_count);
  chain.propertyCount = property_count;
  chain.pProperties = properties;
  terminator_EnumerateInstanceLayerProperties(&chain, &property_count, properties);
  free(properties);
  return 0;
}