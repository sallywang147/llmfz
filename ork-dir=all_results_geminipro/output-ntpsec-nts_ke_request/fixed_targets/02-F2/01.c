#include "ntpd.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define kMinInputLength 20
#define kMaxInputLength 1024

bool nts_ke_request(struct ssl_st *ssl);

extern "C" {
int LLVMFuzzerTestOneInput(const uint8_t *Data, size_t Size) { // ntpsec/tests/ntpd/nts_ke.c

  if (Size < kMinInputLength || Size > kMaxInputLength) {
    return 0;
  }

  struct ntpd_ke_request req;
  memset(&req, 0, sizeof(req));

  req.version = 1;
  req.flags = 0;
  req.key_id = 0;
  req.nonce_len = Size;
  req.nonce = (uint8_t *)Data;

  return nts_ke_request(&req);
}
}