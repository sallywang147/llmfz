#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>

#include "archive.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  // Create an Archive object
  Archive arc;

  // Extract a boolean value from the data stream
  bool EnableBroken = stream.ConsumeBool();

  // Call the target function
  arc.CheckArc(&arc, EnableBroken);

  return 0;
}