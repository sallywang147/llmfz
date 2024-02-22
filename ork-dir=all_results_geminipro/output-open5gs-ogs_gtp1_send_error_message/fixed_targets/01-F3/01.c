#include <stdint.h>
#include <stdio.h>

#include "fuzzing.h"
#include "ogs-gtp.h"

#define kMinInputLength 5
#define kMaxInputLength 1024

extern "C" {
#include "ogs-gtp.h"
}

extern int LLVMFuzzerTestOneInput(const uint8_t *Data, size_t Size) { /* open5gs/tests/non3gpp/gtp-path.c */

  if (Size < kMinInputLength || Size > kMaxInputLength) {
    return 1;
  }

  if (!initialized) {
    initialize();
    ogs_log_install_domain(&__ogs_gtp_domain, "gtp", OGS_LOG_NONE);
    ogs_log_install_domain(&__ogs_tlv_domain, "tlv", OGS_LOG_NONE);
  }

  ogs_gtp_xact_t *xact;
  xact = ogs_gtp_xact_new(NULL, NULL, NULL, NULL);

  if (xact == NULL) {
    return 1;
  }

  ogs_gtp1_send_error_message(xact, 0, 0, 0);

  ogs_gtp_xact_free(xact);

  return 0;
}

bool initialized = false;

void initialize() {
  ogs_init();
  initialized = true;
}