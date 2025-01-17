 #include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "apputils.h"
#include "ns_turn_utils.h"
#include "stun_buffer.h"

extern int LLVMFuzzerTestOneInput(const uint8_t *Data, size_t Size) { // rfc5769check
  if (Size < 10) {
    return 1;
  }

  size_t len = Size;
  stun_set_binding_response_str((uint8_t *)Data, &len, NULL, NULL, 0, NULL, 0, 0, 0);
  return 0;
}