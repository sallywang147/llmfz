#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include "regex.h"

extern "C" {
#include <regex.h>
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  if (size < 16) {
    return 0;
  }
  regmatch_t m;
  m.rm_so = data[0];
  m.rm_eo = data[1];
  char *src = (char *)malloc(size - 16);
  if (src == NULL) {
    return 0;
  }
  memcpy(src, data + 16, size - 16);
  src[size - 16] = '\0';
  char *endptr;
  int base = data[2];
  regex_t regex;
  regcomp(&regex, src, REG_EXTENDED);
  regexec(&regex, src, 1, &m, 0);
  free(src);
  regfree(&regex);
  return 0;
}