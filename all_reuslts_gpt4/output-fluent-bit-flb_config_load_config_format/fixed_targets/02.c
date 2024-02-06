#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "fluent-bit/flb_config.h"
#include "fluent-bit/flb_cf.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  if (size == 0) {
    return 0;
  }

  FuzzedDataProvider provider(data, size);

  // Initialize Fluent Bit library
  struct flb_config *config = flb_config_init();
  if (!config) {
    return 0;
  }

  struct flb_cf *cf = flb_cf_create(config, "fluent-bit");
  if (!cf) {
    flb_config_exit(config);
    return 0;
  }

  // Generate inputs for flb_config_load_config_format
  std::string input_data = provider.ConsumeRemainingBytesAsString();
  cf->cfg = strdup(input_data.c_str());

  // Call the function to fuzz
  flb_config_load_config_format(config, cf);

  // Cleanup
  flb_cf_destroy(cf);
  flb_config_exit(config);

  return 0;
}