#include "libcue.h"
#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

extern "C" {
#include <stdio.h>
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FILE *f = fmemopen((void *)data, size, "r");
  if (!f) {
    return 0;
  }
  struct Cd *cd = cue_parse_file(f);
  if (!cd) {
    fclose(f);
    return 0;
  }
  cd_free(cd);
  fclose(f);
  return 0;
}