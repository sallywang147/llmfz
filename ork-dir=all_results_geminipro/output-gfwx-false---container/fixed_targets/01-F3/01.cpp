#include <stddef.h>
#include <stdint.h>
#include <fuzzer/FuzzedDataProvider.h>
#include <fuzzing/types/Container.h>

extern "C" {
#include <fuzzing/fuzzer_test_common.h>
}

using namespace fuzzing;
using namespace fuzzing::types;

// A fuzzer that reads a sequence of characters and stores them in a
// Container.
void LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider data_provider(data, size);

  // Create a Container to store the characters.
  Container<char, true, false> container;

  // Read the characters from the data provider and store them in the
  // Container.
  while (data_provider.remaining_bytes() > 0) {
    char c = data_provider.ConsumeIntegral<char>();
    container.push_back(c);
  }

  // Destroy the Container.
  container.~Container();
}