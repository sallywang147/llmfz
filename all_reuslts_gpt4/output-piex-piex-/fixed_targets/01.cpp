#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <exception>

#include "piex.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  std::exception exception;
  int integer = stream.ConsumeIntegral<int>();

  piex::(&exception, &integer);

  return 0;
}