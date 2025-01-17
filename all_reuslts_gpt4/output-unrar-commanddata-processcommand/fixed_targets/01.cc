#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "CommandData.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  CommandData commandData;

  // Assuming CommandData has a method to consume data
  // If not, you might need to set its fields manually
  commandData.ConsumeData(stream);

  commandData.ProcessCommand();

  return 0;
}