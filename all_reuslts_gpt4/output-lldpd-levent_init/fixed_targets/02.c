#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>

#include "lldpd.h"
#include "levent.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  struct lldpd cfg;
  cfg.g_config.c_mgmt_pattern = stream.ConsumeRandomLengthString().c_str();
  cfg.g_config.c_cid_pattern = stream.ConsumeRandomLengthString().c_str();
  cfg.g_config.c_iface_pattern = stream.ConsumeRandomLengthString().c_str();
  cfg.g_config.c_descr_pattern = stream.ConsumeRandomLengthString().c_str();
  cfg.g_config.c_platform_pattern = stream.ConsumeRandomLengthString().c_str();

  levent_init(&cfg);

  return 0;
}