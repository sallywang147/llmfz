#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "fluent-bit/flb_config.h"
#include "fluent-bit/flb_cf.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  struct flb_config *config = flb_config_init();
  if (!config) {
    return 0;
  }

  struct flb_cf *cf = flb_cf_create();
  if (!cf) {
    flb_config_exit(config);
    return 0;
  }

  // Consume the remaining bytes as a string and use it as the configuration format.
  std::string config_format = stream.ConsumeRemainingBytesAsString();
  cf->file_content = config_format.c_str();
  cf->file_content_len = config_format.size();

  flb_config_load_config_format(config, cf);

  flb_cf_destroy(cf);
  flb_config_exit(config);

  return 0;
}