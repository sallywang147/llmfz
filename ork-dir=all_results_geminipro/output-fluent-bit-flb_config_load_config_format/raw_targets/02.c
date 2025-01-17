#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>

#include "flb.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  struct flb_config config;
  struct flb_cf cf;

  flb_config_init(&config);
  flb_cf_init(&cf);

  int ret = flb_config_load_config_format(&config, &cf);
  if (ret != 0) {
    return 0;
  }

  flb_config_free(&config);
  flb_cf_free(&cf);

  return 0;
}