#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "CommandData.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider provider(data, size);

  // Assume CommandData has a constructor that takes a string.
  // This will depend on the actual implementation of CommandData.
  std::string command = provider.ConsumeRemainingBytesAsString();
  CommandData commandData(command);

  commandData.ProcessCommand(&commandData);

  return 0;
}