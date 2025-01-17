#include <stdint.h>
#include <stdlib.h>

#include "flexdef.h"
#include "scanopt.h"

extern "C" {
#include "FlexLexer.h"
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  if (size < 1) {
    return 0;
  }
  void *xmalloc_fuzz = malloc(size);
  memcpy(xmalloc_fuzz, data, size);
  int size_fuzz = *(int *)xmalloc_fuzz;
  free(xmalloc_fuzz);
  void *ret = yy_flex_xmalloc(size_fuzz);
  free(ret);
  return 0;
}