#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include <fuzzer/FuzzedDataProvider.h>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider provider(data, size);

  int version;
  int result = vkEnumerateInstanceVersion(&version);
  if (result != VK_SUCCESS) {
    return 0;
  }

  return 0;
}