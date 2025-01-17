#include <fuzzer/FuzzedDataProvider.h>
#include <cstddef>
#include <cstdint>
#include <exception>
#include "piex.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider stream(data, size);

  std::exception *ex = nullptr;
  int orientation = stream.ConsumeIntegral<int>();
  int *ptr = &orientation;

  piex::GetExifOrientation(ex, orientation, ptr);

  return 0;
}