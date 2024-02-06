#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <exception>
#include <vector>

#include "piex.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  
  std::exception *exc = nullptr;
  int orientation = stream.ConsumeIntegral<int>();

  piex::GetOrientation(exc, &orientation);

  return 0;
}