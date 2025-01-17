#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "regex.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  struct regmatch_t m;
  m.rm_so = stream.ConsumeIntegral<regoff_t>();
  m.rm_eo = stream.ConsumeIntegral<regoff_t>();

  std::string src = stream.ConsumeRemainingBytesAsString();
  char* endptr = nullptr;

  int base = stream.ConsumeIntegral<int>();

  regmatch_strtol(&m, src.data(), &endptr, base);

  return 0;
}