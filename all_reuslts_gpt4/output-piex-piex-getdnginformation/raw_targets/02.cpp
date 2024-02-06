#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <vector>
#include <exception>

#include "piex.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  std::exception *ex = nullptr;
  int arg1 = stream.ConsumeIntegral<int>();
  int arg2 = stream.ConsumeIntegral<int>();
  std::vector<uint8_t> arg3 = stream.ConsumeRemainingBytes<uint8_t>();

  piex::GetDngInformation(ex, &arg1, &arg2, &arg3);

  return 0;
}