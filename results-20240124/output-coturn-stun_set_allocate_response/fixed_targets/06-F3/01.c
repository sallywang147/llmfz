#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "apputils.h"
#include "ns_turn_utils.h"
#include "stun_buffer.h"

static SHATYPE shatype = SHATYPE_SHA1;

#define kMinInputLength 10
#define kMaxInputLength 5120

extern "C" {
int LLVMFuzzerTestOneInput(const uint8_t *Data,
                                  size_t Size) { // rfc5769check

  if (Size < kMinInputLength || Size > kMaxInputLength) {
    return 1;
  }

  stun_buffer *buf = stun_buffer_new();
  stun_tid tid;
  stun_set_allocate_response(buf, &tid, NULL, NULL, NULL, 0, 0, 0, NULL, 0, NULL);
  stun_buffer_free(buf);

  return 0;
}
}