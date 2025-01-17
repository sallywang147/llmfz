 #include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "apputils.h"
#include "ns_turn_utils.h"
#include "stun_buffer.h"

#define kMinInputLength 10
#define kMaxInputLength 5120

extern int LLVMFuzzerTestOneInput(const uint8_t *Data,
                                  size_t Size) { // rfc5769check

  if (Size < kMinInputLength || Size > kMaxInputLength) {
    return 1;
  }

  struct _stun_buffer buf;
  stun_init_buffer(&buf, (uint8_t *)Data, Size);
  union ioa_addr peer_addr;
  short channel_number = 0;
  stun_set_channel_bind_request(&buf, &peer_addr, channel_number);

  return 0;
}