#include "ntpd.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define kMinInputLength 20
#define kMaxInputLength 1024

bool nts_ke_request(struct ssl_st * ssl);

extern "C" {
#include <openssl/ssl.h>
}

extern "C" {
int LLVMFuzzerTestOneInput(const uint8_t *Data, size_t Size) { // ntpsec/tests/ntpd/nts_
  return 0;
}
}