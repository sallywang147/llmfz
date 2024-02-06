#include <stdint.h>
#include <stdio.h>

#include "fuzzing.h"
#include "ogs-gtp.h"

#define kMinInputLength 5
#define kMaxInputLength 1024

extern int LLVMFuzzerTestOneInput(const uint8_t *Data, size_t Size) { /* open5gs/tests/non3gpp/gtp-path.c */

  if (Size < kMinInputLength || Size > kMaxInputLength) {
    return 1;
  }

  if (!initialized) {
    initialize();
    ogs_log_install_domain(&__ogs_gtp_domain, "gtp", OGS_LOG_NONE);
    ogs_log_install_domain(&__ogs_tlv_domain, "tlv", OGS_LOG_NONE);
  }

  ogs_gtp_node_t *gnode;
  gnode = ogs_gtp_node_create(NULL);

  if (gnode == NULL) {
    return 1;
  }

  char recovery = Data[0] & 1;
  char features = Data[1] & 1;

  ogs_gtp2_send_echo_request(gnode, recovery, features);

  ogs_gtp_node_destroy(gnode);

  return 0;
}