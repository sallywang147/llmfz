 #include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <string>

#include "fuzzing/types/Container.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  const size_t container_size = stream.ConsumeIntegral<size_t>();
  fuzzing::types::Container<unsigned char, false, false> container(
      container_size);
  for (size_t i = 0; i < container_size; i++) {
    container.data()[i] = stream.ConsumeIntegral<unsigned char>();
  }
  container.~Container();
  return 0;
}