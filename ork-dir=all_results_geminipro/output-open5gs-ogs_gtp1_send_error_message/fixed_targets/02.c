#include <stdint.h>
#include <stdio.h>

#include "fuzzing.h"
#include "ogs-gtp.h"

#define kMinInputLength 5
#define kMaxInputLength 1024

extern "C" {
#include "ogs-gtp-internal.h"
}

// Add the definition of the ogs_gtp1_send_error_message function.
int ogs_gtp1_send_error_message(ogs_gtp_xact_t *xact, uint32_t teid, uint8_t cause, uint8_t offending_ie_type) {
  // Implement the function here.
  return 0;
}

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

  ogs_gtp_xact_t xact;
  ogs_gtp1_send_error_message(&xact, 0x1234, 0x56, 0x78);

  return 0;
}