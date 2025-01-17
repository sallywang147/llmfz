#include "../src/daemon/lldpd.h"
#include <libevent/event.h>

extern "C" {
  #include <libevent/event.h>
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *Data, size_t Size) {
  struct lldpd cfg;
  cfg.g_config.c_mgmt_pattern = NULL;
  cfg.g_config.c_tx_hold = LLDPD_TX_HOLD;

  levent_init(&cfg);
  levent_loop(&cfg);
  levent_cleanup(&cfg);

  return 0;
}

void levent_init(struct lldpd *cfg) {
  event_init();
}

void levent_loop(struct lldpd *cfg) {
  event_dispatch();
}

void levent_cleanup(struct lldpd *cfg) {
  event_base_free(cfg->ev_base);
}