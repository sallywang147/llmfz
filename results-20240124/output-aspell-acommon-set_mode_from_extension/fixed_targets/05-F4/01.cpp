#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "acommon.h"

extern "C" {
#include "acommon.h"
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  acommon::PosibErr config;
  acommon::Config filename;
  char *in = (char *)data;
  int in_len = size;
  struct _IO_FILE *file = NULL;
  acommon::set_mode_from_extension(&config, &filename, in, in_len, file);
  return 0;
}