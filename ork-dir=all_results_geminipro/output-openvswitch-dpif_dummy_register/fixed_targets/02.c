#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>

#include "dpif.h"

extern "C" {
#include "dpif_dummy.h"
}

static void LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  dpif_dummy_register(0);
  dpif_dummy_process_input(data, size);
}