#include <stdint.h>
#include <stdlib.h>

#include "siphash.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  siphash24(data, size, sip_keyof("FUZZING IS FUN!"));
  sip24_valid();
  return 0;
}