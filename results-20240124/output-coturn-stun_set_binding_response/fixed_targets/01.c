#include <stdio.h>
#include <stdlib.h>
#include <string.h>

extern "C" {
#include "apputils.h"
#include "ns_turn_utils.h"
#include "stun_buffer.h"
}

int LLVMFuzzerTestOneInput(const unsigned char *Data,
                                  size_t Size) { // rfc5769check

  if (Size < 100 || Size > 10000) {
    return 1;
  }

  struct _stun_buffer *buf = stun_buffer_create(Size);
  if (!buf) {
    return 1;
  }

  stun_set_binding_response(buf, NULL, NULL, 0, NULL);

  stun_buffer_destroy(buf);

  return 0;
}