#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include <fuzzer/FuzzedDataProvider.h>
#include <regex.h>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider stream(data, size);

  regmatch_t m;
  m.rm_so = stream.ConsumeIntegral<int>();
  m.rm_eo = stream.ConsumeIntegral<int>();

  std::string src = stream.ConsumeRandomLengthString();
  char *endptr;
  int base = stream.ConsumeIntegral<int>();

  regmatch_strtol(&m, src.c_str(), &endptr, base);

  return 0;
}