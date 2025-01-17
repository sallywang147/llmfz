#include <fuzzer/FuzzedDataProvider.h>
#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

extern "C" {
#include <tmp_dir.h>
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider provider(data, size);
  const size_t max_length = 1024;
  std::vector<uint8_t> input_buffer =
      provider.ConsumeBytes<uint8_t>(provider.ConsumeIntegralInRange<size_t>(0, max_length));
  char* input_string = reinterpret_cast<char*>(input_buffer.data());
  char* output_string;
  int ret = tmp_dir(&output_string);
  free(output_string);
  return 0;
}