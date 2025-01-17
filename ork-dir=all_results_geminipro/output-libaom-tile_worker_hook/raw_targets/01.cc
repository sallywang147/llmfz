#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider provider(data, size);

  size_t input_size = provider.ConsumeIntegralInRange<size_t>(0, 1024);
  size_t output_size = provider.ConsumeIntegralInRange<size_t>(0, 1024);

  auto input = provider.ConsumeBytes<char>(input_size);
  auto output = provider.ConsumeBytes<char>(output_size);

  tile_worker_hook(input.data(), output.data());

  return 0;
}