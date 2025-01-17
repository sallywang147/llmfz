The corrected code:
```c++
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "stun.h"

#define kMinInputLength 10
#define kMaxInputLength 5120

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *Data,
                                  size_t Size) { // rfc5769check

  if (Size < kMinInputLength || Size > kMaxInputLength) {
    return 1;
  }

  struct _stun_buffer buf;
  stun_init_buffer(&buf);

  union ioa_addr peer_addr;
  stun_set_channel_bind_request(&buf, &peer_addr, 1);

  stun_free_buffer(&buf);

  return 0;
}