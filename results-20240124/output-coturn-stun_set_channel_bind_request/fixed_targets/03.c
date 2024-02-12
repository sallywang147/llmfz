#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "apputils.h"
#include "ns_turn_utils.h"
#include "stun_buffer.h"

#define kMinInputLength 10
#define kMaxInputLength 5120

extern "C" {
#include "stun_constants.h"
}

extern int LLVMFuzzerTestOneInput(const uint8_t *Data,
                                  size_t Size) { // rfc5769check

  if (Size < kMinInputLength || Size > kMaxInputLength) {
    return 1;
  }

  struct _stun_buffer *buf = stun_buffer_new(Size);
  if (!buf) {
    return 1;
  }

  stun_buffer_set_stun_version(buf, STUN_VERSION_RFC_5389_00);
  stun_buffer_set_stun_method(buf, STUN_METHOD_BINDING);

  stun_set_channel_bind_request(buf, NULL, 0);

  stun_buffer_free(buf);

  return 0;
}