#include <fuzzer/FuzzedDataProvider.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "dict.h"

extern "C" {
#include "dict_regexp.h"
}

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
    dict_regexp_close(dict);  // Fix: Use dict_regexp_close instead of dict_close
  }

  free(str);
  return 0;
}