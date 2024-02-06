#include "../src/daemon/lldpd.h"
#include <event2/event.h>

extern "C" {
#include <stddef.h>
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *Data, size_t Size) {
  struct lldpd cfg;
  levent_init(&cfg);
  return 0;
}