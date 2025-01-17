#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>

#include "archive.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  // Initialize the Archive object
  Archive arcObj;

  // Extract boolean value
  bool enableBroken = stream.ConsumeBool();

  // Call the function under test
  arcObj.CheckArc(&arcObj, enableBroken);

  return 0;
}