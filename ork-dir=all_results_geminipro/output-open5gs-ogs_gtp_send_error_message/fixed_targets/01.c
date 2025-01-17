#include <stdint.h>
#include <stdio.h>

#include "fuzzing.h"
#include "ogs-gtp.h"

#define kMinInputLength 5
#define kMaxInputLength 1024

extern "C" {
#include "ogs-log.h"
}

static bool initialized = false;

extern int LLVMFuzzerTestOneInput(const uint8_t *Data, size_t Size) { /* open5gs/tests/non3gpp/gtp-path.c */

  if (Size < kMinInputLength || Size > kMaxInputLength) {
    return 1;
  }

  if (!initialized) {
    initialize();
    ogs_log_install_domain(&__ogs_gtp_domain, "gtp", OGS_LOG_NONE);
    ogs_log_install_domain(&__ogs_tlv_domain, "tlv", OGS_LOG_NONE);
    initialized = true;
  }

  ogs_gtp_xact_t xact;
  int teid = 0;
  char type = 0;
  char cause_value = 0;

  ogs_gtp_send_error_message(&xact, teid, type, cause_value);

  return 0;
}

void initialize() {
  ogs_gtp_init();
  ogs_tlv_init();
}