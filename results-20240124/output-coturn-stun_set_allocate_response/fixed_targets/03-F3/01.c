#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "apputils.h"
#include "ns_turn_utils.h"
#include "stun_buffer.h"

#include "stun_utils.h" // Add the missing header file

extern "C" {
#include "stun_utils.h" // Wrap the missing header file with extern "C" {}
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *Data,
                                  size_t Size) { // rfc5769check

  if (Size < 10 || Size > 5120) {
    return 1;
  }

  struct _stun_buffer *buf = stun_buffer_new();
  stun_set_allocate_response(buf, NULL, NULL, NULL, NULL, 0, 0, 0, NULL, 0, NULL);

  stun_buffer_free(buf);

  return 0;
}