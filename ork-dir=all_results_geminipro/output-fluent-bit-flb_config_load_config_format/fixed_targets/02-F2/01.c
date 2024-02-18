#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>

#include "flb.h"

extern "C" {
  int flb_config_init(struct flb_config* config);
  int flb_cf_init(struct flb_cf* cf);
  int flb_config_load_config_format(struct flb_config* config, struct flb_cf* cf);
  void flb_config_free(struct flb_config* config);
  void flb_cf_free(struct flb_cf* cf);
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  struct flb_config config;
  struct flb_cf cf;

  if (flb_config_init(&config) != 0) {
    return 0;
  }
  if (flb_cf_init(&cf) != 0) {
    flb_config_free(&config);
    return 0;
  }

  int ret = flb_config_load_config_format(&config, &cf);
  if (ret != 0) {
    flb_config_free(&config);
    flb_cf_free(&cf);
    return 0;
  }

  flb_config_free(&config);
  flb_cf_free(&cf);

  return 0;
}