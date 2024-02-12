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

  uint8_t buf[4096];
  size_t len = 0;
  stun_set_allocate_response_str(buf, &len, NULL, NULL, NULL, NULL, 0, 0, 0,
                                NULL, 0, NULL);
  return 0;
}