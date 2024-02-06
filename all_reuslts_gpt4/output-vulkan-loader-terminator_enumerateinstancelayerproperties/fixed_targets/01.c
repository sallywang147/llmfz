#include <stdint.h>
#include <stdlib.h>
#include <fuzzer/FuzzedDataProvider.h>

#include "loader.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider stream(data, size);

  // Initialize variables
  VkEnumerateInstanceLayerPropertiesChain chain;
  int propertyCount;
  VkLayerProperties properties;

  // Populate data from the fuzzer
  chain.function = reinterpret_cast<PFN_vkEnumerateInstanceLayerProperties>(stream.ConsumeIntegral<uintptr_t>());
  chain.pfnNextGetInstanceProcAddr = reinterpret_cast<PFN_vkGetInstanceProcAddr>(stream.ConsumeIntegral<uintptr_t>());
  chain.u1 = stream.ConsumeIntegral<uint32_t>();
  chain.u2 = stream.ConsumeIntegral<uint32_t>();
  chain.u3 = stream.ConsumeIntegral<uint32_t>();

  propertyCount = stream.ConsumeIntegral<int>();

  properties.specVersion = stream.ConsumeIntegral<uint32_t>();
  properties.implementationVersion = stream.ConsumeIntegral<uint32_t>();
  std::string layerName = stream.ConsumeBytesAsString(VK_MAX_EXTENSION_NAME_SIZE);
  strncpy(properties.layerName, layerName.c_str(), VK_MAX_EXTENSION_NAME_SIZE);
  std::string description = stream.ConsumeBytesAsString(VK_MAX_DESCRIPTION_SIZE);
  strncpy(properties.description, description.c_str(), VK_MAX_DESCRIPTION_SIZE);

  // Call the function to fuzz
  terminator_EnumerateInstanceLayerProperties(&chain, &propertyCount, &properties);

  return 0;
}