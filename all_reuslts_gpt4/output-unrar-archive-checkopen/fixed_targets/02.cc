#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "Archive.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  // Create an Archive object.
  Archive archiveObj;

  // Consume data from the stream to create an integer.
  int name = stream.ConsumeIntegral<int>();

  // Call the function under test.
  archiveObj.CheckOpen(&archiveObj, &name);

  return 0;
}