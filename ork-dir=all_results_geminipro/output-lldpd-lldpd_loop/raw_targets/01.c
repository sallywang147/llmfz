#include "../src/daemon/lldpd.h"
#include "../src/daemon/lldpd_loop.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *Data, size_t Size) {
  struct lldpd cfg;
  cfg.g_config.c_mgmt_pattern = NULL;
  cfg.g_config.c_tx_hold = LLDPD_TX_HOLD;

  lldpd_loop(&cfg);

  return 0;
}