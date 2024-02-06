#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "regex/regex2.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  if (size < 2) {
    return 0;
  }

  FuzzedDataProvider stream(data, size);

  struct parse p;
  p.g = (struct re_guts *) calloc(1, sizeof(struct re_guts));
  p.next = (char *) stream.ConsumeRemainingBytes().data();
  p.end = p.next + size - 2;
  p.error = 0;
  p.ncsalloc = 0;

  int stop = stream.ConsumeIntegral<int>();
  int type = stream.ConsumeIntegral<int>();

  p_bre(&p, stop, type);

  free(p.g);

  return 0;
}