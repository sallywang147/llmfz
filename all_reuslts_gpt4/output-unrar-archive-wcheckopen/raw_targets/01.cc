#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "Archive.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  // Create an Archive object
  Archive archive;

  // Extract an integer value
  int name = stream.ConsumeIntegral<int>();

  // Call the function with the extracted values
  archive.WCheckOpen(&archive, &name);

  return 0;
}