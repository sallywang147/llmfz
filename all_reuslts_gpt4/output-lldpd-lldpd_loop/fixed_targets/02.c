#include <fuzzer/FuzzedDataProvider.h>
#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>
#include "lldpd.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  struct lldpd *cfg = (struct lldpd*) calloc(1, sizeof(struct lldpd));
  if (!cfg) {
    return 0;
  }

  cfg->g_config.c_mgmt_pattern = stream.ConsumeBytesAsString(stream.remaining_bytes()).c_str();

  lldpd_loop(cfg);

  free(cfg);

  return 0;
}