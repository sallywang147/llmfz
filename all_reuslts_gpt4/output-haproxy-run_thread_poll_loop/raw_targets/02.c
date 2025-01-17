#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider provider(data, size);

  std::string str = provider.ConsumeRemainingBytesAsString();
  char *input_data = const_cast<char *>(str.c_str());

  char *result = run_thread_poll_loop(input_data);

  return 0;
}