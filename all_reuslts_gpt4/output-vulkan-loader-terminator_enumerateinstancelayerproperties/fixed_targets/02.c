#include <stdint.h>
#include <stdlib.h>

#include "loader.h"
#include "fuzzer/FuzzedDataProvider.h"

/*
 * Targets the instance layer properties enumeration.
 */
extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider stream(data, size);

  VkEnumerateInstanceLayerPropertiesChain chain = {};
  int count = stream.ConsumeIntegral<int>();
  VkLayerProperties properties = {};

  terminator_EnumerateInstanceLayerProperties(&chain, &count, &properties);

  return 0;
}