#include <fuzzer/FuzzedDataProvider.h>
#include <cstddef>
#include <cstdint>
#include <exception>
#include <vector>
#include "piex.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  
  std::vector<char> exception_data = stream.ConsumeBytes<char>(stream.remaining_bytes());
  std::exception ex = std::exception(exception_data.data());

  int orientation = stream.ConsumeIntegral<int>();

  piex::GetOrientation(&ex, &orientation);

  return 0;
}