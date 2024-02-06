#include "../src/daemon/lldpd.h"
#include <libevent/event.h>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *Data, size_t Size) {
  struct lldpd cfg;
  cfg.g_config.c_mgmt_pattern = NULL;
  cfg.g_config.c_tx_hold = LLDPD_TX_HOLD;

  levent_loop(&cfg);

  return 0;
}