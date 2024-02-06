#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "wavpack.h"

extern "C" {
#include "wavpack_local.h"
}

int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  WavpackContext *wpc = WavpackOpenFileInput(data, size);
  if (!wpc) {
    return 0;
  }
  WavpackSeekSample(wpc, 0);
  WavpackCloseFile(wpc);
  return 0;
}