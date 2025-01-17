#include <stdint.h>
#include <stdlib.h>

#include "vulkan/vulkan.h"
#include "fuzzer/FuzzedDataProvider.h"

/*
 * Targets the enumeration of instance layer properties.
 */
extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider stream(data, size);

  // Extract an integer value
  int propertyCount = stream.ConsumeIntegral<int>();

  // Create a VkLayerProperties object
  VkLayerProperties* pProperties = (VkLayerProperties*) malloc(sizeof(VkLayerProperties) * propertyCount);
  if (pProperties == NULL) {
    return 0;
  }

  // Call the target function
  vkEnumerateInstanceLayerProperties(&propertyCount, pProperties);

  // Clean up
  free(pProperties);

  return 0;
}