#include "../src/daemon/lldpd.h"

#define kMinInputLength 5
#define kMaxInputLength 2048

/* Use this callback to avoid some logs */
void donothing(int pri, const char *msg) {};

extern "C" {
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <edp/edp.h>
}

extern int LLVMFuzzerTestOneInput(const uint8_t *Data, size_t Size) {
  if (Size < kMinInputLength || Size > kMaxInputLength) {
    return 1;
  }

  struct lldpd cfg;
  cfg.g_config.c_mgmt_pattern = NULL;
  cfg.g_config.c_tx_hold = LLDPD_TX_HOLD;

  struct lldpd_chassis *nchassis = NULL;
  struct lldpd_port *nport = NULL;
  struct lldpd_hardware hardware;
  TAILQ_INIT(&hardware.h_rports);
  log_register(donothing);

  edp_decode(&cfg, (char *)Data, Size, &hardware, &nchassis, &nport);

  if (!nchassis || !nport) {
    return 1;
  }

  lldpd_port_cleanup(nport, 1);
  free(nport);
  lldpd_chassis_cleanup(nchassis, 1);

  lldpd_loop(&cfg);

  return 0;
}