#include <stdint.h>
#include <stdio.h>

#include "fuzzing.h"
#include "ogs-gtp.h"

#define kMinInputLength 5
#define kMaxInputLength 1024

extern int LLVMFuzzerTestOneInput(const uint8_t *Data, size_t Size) { 

  if (Size < kMinInputLength || Size > kMaxInputLength) {
    return 1;
  }

  if (!initialized) {
    initialize();
    ogs_log_install_domain(&__ogs_gtp_domain, "gtp", OGS_LOG_NONE);
    ogs_log_install_domain(&__ogs_tlv_domain, "tlv", OGS_LOG_NONE);
  }

  ogs_pkbuf_t *pkbuf;
  pkbuf = ogs_pkbuf_alloc(NULL, OGS_MAX_SDU_LEN);

  if (pkbuf == NULL) {
    return 1;
  }
  ogs_pkbuf_put_data(pkbuf, Data, Size);

  ogs_gtp_node_t gnode;
  gnode.pkbuf = pkbuf;

  ogs_gtp1_send_echo_request(&gnode);

  ogs_pkbuf_free(pkbuf);

  return 0;
}