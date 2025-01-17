#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "apputils.h"
#include "ns_turn_utils.h"
#include "stun_buffer.h"

static SHATYPE shatype = SHATYPE_SHA1;

#define kMinInputLength 10
#define kMaxInputLength 5120

extern int LLVMFuzzerTestOneInput(const uint8_t *Data,
                                  size_t Size) { // rfc5769check

  if (Size < kMinInputLength || Size > kMaxInputLength) {
    return 1;
  }

  struct _stun_buffer *buf = stun_buffer_new();
  struct stun_tid tid;
  union ioa_addr reflexive_addr;
  int error_code = 0;
  char *reason = "reason";

  stun_set_binding_response(buf, &tid, &reflexive_addr, error_code, reason);

  stun_buffer_free(buf);

  return 0;
}