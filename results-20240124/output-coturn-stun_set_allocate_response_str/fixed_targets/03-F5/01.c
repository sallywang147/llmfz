#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "apputils.h"
#include "ns_turn_utils.h"
#include "stun_buffer.h"

extern "C" {
#include "stun_tid.h"
}

extern int LLVMFuzzerTestOneInput(const uint8_t *Data,
                                  size_t Size) { // rfc5769check

  if (Size < 10 || Size > 5120) {
    return 1;
  }

  char buf[5120];
  size_t len = 5120;
  struct stun_tid tid;
  union ioa_addr relayed_addr1;
  union ioa_addr relayed_addr2;
  union ioa_addr reflexive_addr;
  int lifetime = 0;
  int max_lifetime = 0;
  int error_code = 0;
  char reason[256];
  size_t reservation_token = 0;
  char mobile_id[256];

  stun_set_allocate_response_str(buf, &len, &tid, &relayed_addr1,
                                 &relayed_addr2, &reflexive_addr, lifetime,
                                 max_lifetime, error_code, reason,
                                 reservation_token, mobile_id);

  return 0;
}