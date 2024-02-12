 #include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "apputils.h"
#include "ns_turn_utils.h"
#include "stun_buffer.h"

extern int LLVMFuzzerTestOneInput(const uint8_t *Data,
                                  size_t Size) { // rfc5769check

  if (Size < 10 || Size > 5120) {
    return 1;
  }

  struct _stun_buffer *buf = stun_buffer_new();
  if (!buf) {
    return 1;
  }

  struct stun_tid *tid = (struct stun_tid *) malloc(sizeof(struct stun_tid));
  if (!tid) {
    stun_buffer_free(buf);
    return 1;
  }

  union ioa_addr reflexive_addr;

  stun_set_binding_response(buf, tid, &reflexive_addr, 0, NULL);

  stun_buffer_free(buf);
  free(tid);

  return 0;
}