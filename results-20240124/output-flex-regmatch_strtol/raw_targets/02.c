 #include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include <fuzzer/FuzzedDataProvider.h>

#include <regex.h>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider stream(data, size);
  struct regmatch_t match;
  char *src = (char *)stream.ConsumeBytesAsString(stream.ConsumeIntegralInRange(0, 100)).c_str();
  char *endptr;
  int base = stream.ConsumeIntegralInRange(2, 36);
  int ret = regmatch_strtol(&match, src, &endptr, base);
  return 0;
}