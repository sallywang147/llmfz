#include <cstdint>
#include <cstdlib>
#include <cstring>
#include <fuzzer/FuzzedDataProvider.h>

extern "C" {
#include <regex.h>
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  char src[1024];
  size_t src_len = stream.ConsumeRemainingBytes(src, sizeof(src));

  regmatch_t match;
  match.rm_so = stream.ConsumeIntegral<int>();
  match.rm_eo = stream.ConsumeIntegral<int>();

  char* endptr;
  int base = stream.ConsumeIntegral<int>();

  regex_strtol(&match, src, &endptr, base);

  return 0;
}