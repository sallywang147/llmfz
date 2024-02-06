#include <fuzzer/FuzzedDataProvider.h>
#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include <libthread_pool.h>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider provider(data, size);
  const size_t input_size = provider.ConsumeIntegralInRange<size_t>(0, 10000);
  std::vector<uint8_t> input_data = provider.ConsumeBytes<uint8_t>(input_size);
  char *input_data_ptr = reinterpret_cast<char *>(input_data.data());

  char *output = run_thread_poll_loop(input_data_ptr);
  free(output);

  return 0;
}