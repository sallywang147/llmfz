#include <fuzzer/FuzzedDataProvider.h>
#include <cstddef>
#include <cstdint>
#include <vector>
#include "fuzzing/datasource/datasource.hpp"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  size_t max = stream.ConsumeIntegral<size_t>();
  size_t id = stream.ConsumeIntegral<size_t>();
  size_t lastParam = stream.ConsumeIntegral<size_t>();

  std::vector<uint8_t> thisVector = stream.ConsumeRemainingBytes<uint8_t>();
  
  fuzzing::datasource::Datasource min(&thisVector);

  fuzzing::datasource::Datasource datasource(&thisVector);

  datasource.get(&min, max, id, lastParam);

  return 0;
}