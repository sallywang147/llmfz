#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include "fuzzer/FuzzedDataProvider.h"
#include "loader.h"

/*
 * Targets the device dispatch table lookup.
 */
extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider stream(data, size);

  // Extract values from the stream
  std::string str1 = stream.ConsumeRandomLengthString();
  std::string str2 = stream.ConsumeRandomLengthString();

  // Initialize VkLayerDispatchTable
  VkLayerDispatchTable dispatchTable = {};

  // Call the target function
  char* result = loader_lookup_device_dispatch_table(&dispatchTable, str1.c_str(), str2.c_str());

  return 0;
}