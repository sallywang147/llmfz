#include <fuzzer/FuzzedDataProvider.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "dict.h"

struct DICT *dict_regexp_open(char *, int, int);

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider fdp(data, size);

  size_t len = fdp.ConsumeIntegralInRange<size_t>(0, 1024);
  char *str = (char *)malloc(len + 1);
  fdp.ConsumeBytes(str, len);
  str[len] = '\0';

  int flags = fdp.ConsumeIntegralInRange<int>(0, 10);
  int opts = fdp.ConsumeIntegralInRange<int>(0, 10);

  struct DICT *dict = dict_regexp_open(str, flags, opts);
  if (dict) {
    dict_close(dict);
  }

  free(str);
  return 0;
}