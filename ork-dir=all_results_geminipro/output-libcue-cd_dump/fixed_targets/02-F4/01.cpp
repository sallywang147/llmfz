#include "libcue.h"
#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

extern "C" {
#include "libcue.h"
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  struct Cd cd;
  if (cd_parse(&cd, data, size) == 0) {
    cd_dump(&cd);
  }
  cd_free(&cd);  // Free the allocated memory for the Cd struct
  return 0;
}