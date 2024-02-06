#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <vector>

#include "Zydis/Zydis.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  const size_t bufferSize = stream.ConsumeIntegralInRange<size_t>(0, 1000);
  std::vector<char> buffer(bufferSize);

  ZydisEncoderNopFill(buffer.data(), bufferSize);

  return 0;
}