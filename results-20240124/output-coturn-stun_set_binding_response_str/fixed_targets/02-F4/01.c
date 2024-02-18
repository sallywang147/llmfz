#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "apputils.h"
#include "ns_turn_utils.h"
#include "stun_buffer.h"

#define kMinInputLength 10
#define kMaxInputLength 5120

extern "C" {
#include "stun_buffer_types.h"
}

static SHATYPE shatype = SHATYPE_SHA1;

extern int LLVMFuzzerTestOneInput(const uint8_t *Data,
                                  size_t Size) { // rfc5769check

  if (Size < kMinInputLength || Size > kMaxInputLength) {
    return 1;
  }

  size_t len = 0;
  struct stun_tid tid;
  union ioa_addr reflexive_addr;
  int error_code = 0;
  char reason[100] = {0};
  int cookie = 0;
  int old_stun = 0;
  int no_stun_backward_compatibility = 0;

  stun_set_binding_response_str((char *)Data, &len, &tid, &reflexive_addr,
                                error_code, reason, cookie, old_stun,
                                no_stun_backward_compatibility);

  return 0;
}