#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

extern "C" int sam_index_build3(char * fn, char * fnidx, int min_shift, int nthreads);

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider provider(data, size);

  std::string fn = provider.ConsumeRandomLengthString();
  std::string fnidx = provider.ConsumeRemainingBytesAsString();
  int min_shift = provider.ConsumeIntegral<int>();
  int nthreads = provider.ConsumeIntegral<int>();

  sam_index_build3(const_cast<char*>(fn.c_str()), const_cast<char*>(fnidx.c_str()), min_shift, nthreads);

  return 0;
}