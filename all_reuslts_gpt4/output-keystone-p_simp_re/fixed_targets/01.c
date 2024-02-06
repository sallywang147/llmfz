#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>

#include "regex/regex2.h"

struct parse p;

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider stream(data, size);

  int int_arg = stream.ConsumeIntegral<int>();

  p_simp_re(&p, int_arg);

  return 0;
}