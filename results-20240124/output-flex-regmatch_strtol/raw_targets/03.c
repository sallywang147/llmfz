 #include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include <fuzzer/FuzzedDataProvider.h>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider stream(data, size);

  struct regmatch_t m;
  m.rm_so = stream.ConsumeIntegral<int>();
  m.rm_eo = stream.ConsumeIntegral<int>();

  char *src = stream.ConsumeRandomLengthString().c_str();
  char *endptr;
  int base = stream.ConsumeIntegral<int>();

  regmatch_strtol(&m, src, &endptr, base);

  return 0;
}