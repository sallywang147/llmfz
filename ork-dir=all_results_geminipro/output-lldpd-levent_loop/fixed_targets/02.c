#include <levent.h>
#include "../src/daemon/lldpd.h"

extern "C" {
#include <llvm/FuzzMutator.h>
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  struct lldpd cfg;
  cfg.g_config.c_mgmt_pattern = NULL;
  cfg.g_config.c_tx_hold = LLDPD_TX_HOLD;
  levent_loop(&cfg);
  return 0;
}