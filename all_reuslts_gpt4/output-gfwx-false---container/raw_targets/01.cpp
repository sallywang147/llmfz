#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "fuzzing/types/Container.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  // Create a container object
  fuzzing::types::Container<char, true, false> container;

  // Fill the container with data from the fuzzer
  while (stream.remaining_bytes() > 0) {
    container.Add(stream.ConsumeIntegral<char>());
  }

  // Explicitly call the destructor
  container.~Container();

  return 0;
}