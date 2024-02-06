#include "ntpd.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define kMinInputLength 20
#define kMaxInputLength 1024

bool nts_ke_request(struct ssl_st *ssl);

extern int LLVMFuzzerTestOneInput(const uint8_t *Data, size_t Size) { // ntpsec/tests/ntpd/nts_ke.c

  if (Size < kMinInputLength || Size > kMaxInputLength) {
    return 0;
  }

  struct ssl_st ssl;

  ssl.s3->hs.state = SSL3_ST_SW_HELLO_REQ_A;
  ssl.s3->hs.tmp.new_cipher = 0x0000;
  ssl.s3->hs.tmp.new_cipher = 0x0000;
  ssl.s3->hs.tmp.new_cipher = 0x0000;
  ssl.s3->hs.tmp.new_cipher = 0x0000;
  ssl.s3->hs.tmp.new_cipher = 0x0000;
  ssl.s3->hs.tmp.new_cipher = 0x0000;
  ssl.s3->hs.tmp.new_cipher = 0x0000;
  ssl.s3->hs.tmp.new_cipher = 0x0000;
  ssl.s3->hs.tmp.new_cipher = 0x0000;
  ssl.s3->hs.tmp.new_cipher = 0x0000;
  ssl.s3->hs.tmp.new_cipher = 0x0000;
  ssl.s3->hs.tmp.new_cipher = 0x0000;
  ssl.s3->hs.tmp.new_cipher = 0x0000;
  ssl.s3->hs.tmp.new_cipher = 0x0000;
  ssl.s3->hs.tmp.new_cipher = 0x0000;
  ssl.s3->hs.tmp.new_cipher = 0x0000;
  ssl.s3->hs.tmp.new_cipher = 0x0000;
  ssl.s3->hs.tmp.new_cipher = 0x0000;
  ssl.s3->hs.tmp.new_cipher = 0x0000;
  ssl.s3->hs.tmp.new_cipher = 0x0000;
  ssl.s3->hs.tmp.new_cipher = 0x0000;
  ssl.s3->hs.tmp.new_cipher = 0x0000;
  ssl.s3->hs.tmp.new_cipher = 0x0000;
  ssl.s3->hs.tmp.new_cipher = 0x0000;
  ssl.s3->hs.tmp.new_cipher = 0x0000;
  ssl.s3->hs.tmp.new_cipher = 0x0000;
  ssl.s3->hs.tmp.new_cipher = 0x0000;
  ssl.s3->hs.tmp.new_cipher = 0x0000;
  ssl.s3->hs.tmp.new_cipher = 0x0000;
  ssl.s3->hs.tmp.new_cipher = 0x0000;
  ssl.s3->hs.tmp.new_cipher = 0x0000;
  ssl.s3->hs.tmp.new_cipher = 0x0000;
  ssl.s3->hs.tmp.new_cipher = 0x0000;
  ssl.s3->hs.tmp.new_cipher = 0x0000;
  ssl.s3->hs.tmp.new_cipher = 0x0000;
  ssl.s3->hs.tmp.new_cipher = 0x0000;
  ssl.s3->hs.tmp.new_cipher = 0x0000;
  ssl.s3->hs.tmp.new_cipher = 0x0000;
  ssl.s3->hs.tmp.new_cipher = 0x0000;
  ssl.s3->hs.tmp.new_cipher = 0x0000;
  ssl.s3->hs.tmp.new_cipher = 0x0000;
  ssl.s3->hs.tmp.new_cipher = 0x0000;
  ssl.s3->hs.tmp.new_cipher = 0x0000;
  ssl.s3->hs.tmp.new_cipher = 0x0000;
  ssl.s3->hs.tmp.new_cipher = 0x0000;
  ssl.s3->hs.tmp.new_cipher = 0x0000;
  ssl.s3->hs.tmp.new_cipher = 0x0000;
  ssl.s3->hs.tmp.new_cipher = 0x0000;
  ssl.s3->hs.tmp.new_cipher = 0x0000;
  ssl.s3->hs.tmp.new_cipher = 0x0000;
  ssl.s3->hs.tmp.new_cipher = 0x0000;
  ssl.s3->hs.tmp.new_cipher = 0x0000;
  ssl.s3->hs.tmp.new_cipher = 0x0000;
  ssl.s3->hs.tmp.new_cipher = 0x0000;
  ssl.s3->hs.tmp.new_cipher = 0x0000;
  ssl.s3->hs.tmp.new_cipher = 0x0000;
  ssl.s3->hs.tmp.new_cipher = 0x0000;
  ssl.s3->hs.tmp.new_cipher = 0x0000;
  ssl.s3->hs.tmp.new_cipher = 0x0000;
  ssl.s3->hs.tmp.new_cipher = 0x0000;
  ssl.s3->hs.tmp.new_cipher = 0x0000;
  ssl.s3->hs.tmp.new_cipher = 0x0000;
  ssl.s3->hs.tmp.new_cipher = 0x0000;
  ssl.s3->hs.tmp.new_cipher = 0x0000;
  ssl.s3->hs.tmp.new_cipher = 0x0000;
  ssl.s3->hs.tmp.new_cipher = 0x0000;
  ssl.s3->hs.tmp.new_cipher = 0x0000;
  ssl.s3->hs.tmp.new_cipher = 0x0000;
  ssl.s3->hs.tmp.new_cipher = 0x0000;
  ssl.s3->hs.tmp.new_cipher = 0x0000;
  ssl.s3->hs.tmp.new_cipher = 0x0000;
  ssl.s3->hs.tmp.new_cipher = 0x0000;
  ssl.s3->hs.tmp.new_cipher = 0x0000;
  ssl.s3->hs.tmp.new_cipher = 0x0000;
  ssl.s3->hs.tmp.new_cipher = 0x0000;
  ssl.s3->hs.tmp.new_cipher = 0x0000;
  ssl.s3->hs.tmp.new_cipher = 0x0000;
  ssl.s3->hs.tmp.new_cipher = 0x0000;
  ssl.s3->hs.tmp.new_cipher = 0x0000;
  ssl.s3->hs.tmp.new_cipher = 0x0000;
  ssl.s3->hs.tmp.new_cipher = 0x0000;
  ssl.s3->hs.tmp.new_cipher = 