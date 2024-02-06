#include "ntpd.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define kMinInputLength 20
#define kMaxInputLength 1024

bool nts_probe(struct peer *peer);

extern int LLVMFuzzerTestOneInput(const uint8_t *Data, size_t Size) { // ntpsec/tests/ntpd/nts_client.c

  if (Size < kMinInputLength || Size > kMaxInputLength) {
    return 0;
  }

  struct peer peer;

  peer.nts_state.aead = 42; /* Dummy init values */
  peer.nts_state.cookielen = 0;
  peer.nts_state.writeIdx = 0;
  peer.nts_state.count = 0;

  peer.srcadr.sa4.sin_family = AF_INET;
  peer.srcadr.sa4.sin_port = htons(9999);
  peer.srcadr.sa4.sin_addr.