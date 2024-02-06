#include "ntpd.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

bool nts_probe(struct peer *peer);

extern int LLVMFuzzerTestOneInput(const uint8_t *Data, size_t Size) { // ntpsec/tests/ntpd/nts_client.c
  struct peer peer;

  peer.nts_state.aead = 42; /* Dummy init values */
  peer.nts_state.cookielen = 0;