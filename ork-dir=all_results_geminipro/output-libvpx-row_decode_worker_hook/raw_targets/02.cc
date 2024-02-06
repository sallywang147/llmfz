#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider provider(data, size);
  size_t input_size = provider.ConsumeIntegralInRange<size_t>(0, size);
  size_t output_size = provider.ConsumeIntegralInRange<size_t>(0, size);
  std::vector<char> input_buffer(input_size);
  std::vector<char> output_buffer(output_size);
  provider.ConsumeBytes(input_buffer.data(), input_size);
  row_decode_worker_hook(input_buffer.data(), output_buffer.data());
  return 0;
}