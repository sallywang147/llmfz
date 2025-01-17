#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <vector>

#include "fuzzing/datasource/datasource.hpp"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  fuzzing::datasource::Datasource ds(stream.ConsumeRemainingBytes<uint8_t>());

  std::vector<uint8_t> min_vector;
  size_t max = stream.ConsumeIntegral<size_t>();
  size_t id = stream.ConsumeIntegral<size_t>();
  size_t size = stream.ConsumeIntegral<size_t>();

  ds.get(&min_vector, &ds, max, id, size);

  return 0;
}