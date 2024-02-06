#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

extern "C" {
#include "re.h"
}

int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  struct parse *p = NULL;
  if (pcre_compile((const char *)data, 0, &p, NULL, NULL, NULL) != 0) {
    return 0;
  }
  pcre_simp_compile(p, 0);
  pcre_free(p);
  return 0;
}