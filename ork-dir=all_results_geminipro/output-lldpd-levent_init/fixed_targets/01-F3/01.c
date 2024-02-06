#include "../src/daemon/lldpd.h"
#include <libevent/event.h>

extern "C" {
  #include <libevent/event.h>
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *Data, size_t Size) {
  struct lldpd cfg;
  levent_init2(&cfg, 0);  // Fix: Use levent_init2 instead of levent_init
  return 0;
}