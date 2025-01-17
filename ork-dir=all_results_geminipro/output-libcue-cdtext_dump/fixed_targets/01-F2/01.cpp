#include "libcue.h"
#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  struct Cdtext *cdtext = cdtext_parse(data, size);
  if (!cdtext) {
    return 0;
  }
  cdtext_dump(cdtext, 0);
  cdtext_free(cdtext);
  return 0;
}