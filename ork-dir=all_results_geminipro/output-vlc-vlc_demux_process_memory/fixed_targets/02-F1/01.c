#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include "vlc/vlc.h"

extern "C" {
#include "vlc/vlc.h"
}

int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  struct vlc_run_args args;
  vlc_run_args_init(&args);
  vlc_demux_process_memory(&args, (char *)data, size);
  return 0;
}