#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "fuzzing/types/Container.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider provider(data, size);

  // Create an instance of the Container class
  fuzzing::types::Container<char, true, false> container;

  // Fill the container with data from the fuzzer
  while (provider.remaining_bytes() > 0) {
    container.Add(provider.ConsumeIntegral<char>());
  }

  // Explicitly call the destructor
  container.~Container();

  return 0;
}