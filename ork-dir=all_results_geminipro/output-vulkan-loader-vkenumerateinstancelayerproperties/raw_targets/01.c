#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include "loader.h"

int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  int count = 0;
  VkLayerProperties *props = NULL;
  int result = vkEnumerateInstanceLayerProperties(&count, props);
  if (result != VK_SUCCESS) {
    return 0;
  }

  props = (VkLayerProperties *)malloc(sizeof(VkLayerProperties) * count);
  result = vkEnumerateInstanceLayerProperties(&count, props);
  if (result != VK_SUCCESS) {
    return 0;
  }

  free(props);

  return 0;
}