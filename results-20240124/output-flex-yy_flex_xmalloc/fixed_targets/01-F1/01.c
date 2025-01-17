#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include "flexdef.h"
#include "options.h"

extern "C" {
int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  if (size < 24) {
    return 0;
  }
  char opt_fuzz[24];

  memcpy(opt_fuzz, data, 23);
  opt_fuzz[23] = 0;
  data += 23;
  size -= 23;

  char *new_str = (char *)malloc(size + 1);
  if (new_str == NULL) {
    return 0;
  }
  memcpy(new_str, data, size);
  new_str[size] = '\0';
  char *ptr = (char *)yy_flex_xmalloc(atoi(new_str));
  free(ptr);
  free(new_str);
  return 0;
}
}