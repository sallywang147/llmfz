#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  size_t max_size = stream.ConsumeIntegral<size_t>();
  int seed = stream.ConsumeIntegral<int>();

  std::string str = stream.ConsumeRemainingBytesAsString();
  char *buf = const_cast<char*>(str.c_str());

  size_t newSize = LLVMFuzzerCustomMutator(buf, size, max_size, seed);

  return 0;
}