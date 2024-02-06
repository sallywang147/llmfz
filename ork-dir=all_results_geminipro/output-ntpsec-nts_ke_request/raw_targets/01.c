#include "ntpd.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define kMinInputLength 20
#define kMaxInputLength 1024

bool nts_ke_request(struct ssl_st * ssl);

extern int LLVMFuzzerTestOneInput(const uint8_t *Data, size_t Size) { // ntpsec/tests/ntpd/nts_client.c

  if (Size < kMinInputLength || Size > kMaxInputLength) {
    return 0;
  }

  struct ssl_st ssl;

  ssl.s3->tmp.new_cipher = 42; /* Dummy init values */
  ssl.s3->tmp.new_cipher->algorithm_auth = SSL_aNULL;
  ssl.s3->tmp.new_cipher->algorithm_enc = SSL_eNULL;
  ssl.s3->tmp.new_cipher->algorithm_mac = SSL_MAC_NULL;

  ssl.s3->tmp.new_compression = 0;
  ssl.s3->tmp.new_cipher->strength_bits = 0;

  ssl.s3->tmp.new_hash = 0;

  ssl.s3->tmp.new_sym_enc = 0;
  ssl.s3->tmp.new_sym_cipher = 0;
  ssl.s3->tmp.new_mac_key = 0;

  return nts_ke_request(&ssl);
}