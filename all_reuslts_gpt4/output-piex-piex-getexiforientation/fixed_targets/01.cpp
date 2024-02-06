#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <vector>

#include "piex.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  std::exception* exception_ptr = nullptr;
  int arg = stream.ConsumeIntegral<int>();
  int result;

  piex::GetExifOrientation(exception_ptr, arg, &result);

  return 0;
}