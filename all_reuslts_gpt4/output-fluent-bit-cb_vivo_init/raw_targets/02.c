#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "fluent-bit/flb_output.h"
#include "fluent-bit/flb_config.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  // Initialize Fluent Bit instance
  struct flb_config *config = flb_config_init();
  if (!config) {
    return 0;
  }

  // Create output instance
  struct flb_output_instance *ins = flb_output_create(config, "vivo", NULL);
  if (!ins) {
    flb_config_exit(config);
    return 0;
  }

  // Consume data as string
  std::string data_str = stream.ConsumeRemainingBytesAsString();

  // Call the function to be fuzzed
  int ret = cb_vivo_init(ins, config, data_str.c_str());

  // Clean up
  flb_output_instance_destroy(ins);
  flb_config_exit(config);

  return 0;
}