#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "ihevce_api.h"

extern "C" {
#include "ihevce_api_internal.h"
}

int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  ihevce_pre_enc_process_frame_thrd((char *)data);
  return 0;
}