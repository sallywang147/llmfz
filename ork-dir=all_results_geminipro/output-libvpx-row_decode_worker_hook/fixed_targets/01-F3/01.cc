#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

extern "C" {
#include "row_decode_worker.h"
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider provider(data, size);
  const size_t input_size = provider.ConsumeIntegralInRange<size_t>(0, size);
  const size_t output_size = provider.ConsumeIntegralInRange<size_t>(0, size);
  auto input = provider.ConsumeBytes<char>(input_size);
  auto output = provider.ConsumeBytes<char>(output_size);
  row_decode_worker(input.data(), input_size, output.data(), output_size);
  return 0;
}