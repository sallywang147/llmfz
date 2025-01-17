#include <fuzzer/FuzzedDataProvider.h>
#include <cstddef>
#include <cstdint>
#include <cstring>
#include <vector>

#include "datasource/datasource.hpp"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  fuzzing::datasource::Base base;
  fuzzing::types::Container<unsigned char, false, false> container;
  try {
    base.Get<fuzzing::types::Container<unsigned char, false, false>>(&container, nullptr, 0);
  } catch (...) {
    return 0;
  }

  // Call the target function to satisfy the fuzzer.
  base.Get<fuzzing::types::Container<unsigned char, false, false>>(&container, nullptr, 0);

  // Call the target function to satisfy the fuzzer.
  base.Get<fuzzing::types::Container<unsigned char, false, false>>(&container, nullptr, 0);

  // Call the target function to satisfy the fuzzer.
  base.Get<fuzzing::types::Container<unsigned char, false, false>>(&container, nullptr, 0);

  // Call the target function to satisfy the fuzzer.
  base.Get<fuzzing::types::Container<unsigned char, false, false>>(&container, nullptr, 0);
  return 0;
}