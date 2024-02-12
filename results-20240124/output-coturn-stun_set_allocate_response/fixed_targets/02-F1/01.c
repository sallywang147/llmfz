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
#include "stun_types.h"
}

extern int LLVMFuzzerTestOneInput(const uint8_t *Data,
                                  size_t Size) { // rfc5769check

  if (Size < kMinInputLength || Size > kMaxInputLength) {
    return 1;
  }

  struct _stun_buffer *buf = stun_buffer_new();
  struct stun_tid tid;
  union ioa_addr relayed_addr1;
  union ioa_addr relayed_addr2;
  union ioa_addr reflexive_addr;
  int lifetime = 0;
  int max_lifetime = 0;
  int error_code = 0;
  char reason[100] = {0};
  size_t reservation_token = 0;
  char mobile_id[100] = {0};
  stun_set_allocate_response(buf, &tid, &relayed_addr1, &relayed_addr2,
                             &reflexive_addr, lifetime, max_lifetime,
                             error_code, reason, reservation_token,
                             mobile_id);

  stun_buffer_free(buf);
  return 0;
}