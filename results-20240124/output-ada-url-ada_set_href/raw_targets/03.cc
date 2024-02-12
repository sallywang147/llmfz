 #include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider provider(data, size);
  const size_t input_size = provider.ConsumeIntegralInRange<size_t>(0, 1024);
  std::vector<uint8_t> input_buffer(input_size);
  provider.ConsumeBytes<uint8_t>(input_buffer.data(), input_size);

  const size_t output_size = provider.ConsumeIntegralInRange<size_t>(0, 1024);
  std::vector<uint8_t> output_buffer(output_size);
  bool ret = ada_set_href(reinterpret_cast<char*>(output_buffer.data()),
                          reinterpret_cast<char*>(input_buffer.data()),
                          input_size);
  if (!ret) {
    return 0;
  }
  return 0;
}