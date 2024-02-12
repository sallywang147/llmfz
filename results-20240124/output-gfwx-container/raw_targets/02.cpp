 #include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>

#include "fuzzing/types/container.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  const size_t capacity = stream.ConsumeIntegral<size_t>();
  fuzzing::types::Container<unsigned char, false, false> container(capacity);
  container.~Container();
  return 0;
}