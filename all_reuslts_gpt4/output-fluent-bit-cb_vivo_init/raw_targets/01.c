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

  // Initialize Fluent Bit output instance and configuration
  struct flb_output_instance *ins = flb_output_create();
  struct flb_config *config = flb_config_init();

  // Consume the data as a string
  std::string data_str = stream.ConsumeRemainingBytesAsString();
  char *data_ptr = const_cast<char *>(data_str.c_str());

  // Call the function to fuzz
  int ret = cb_vivo_init(ins, config, data_ptr);

  // Clean up
  flb_output_instance_destroy(ins);
  flb_config_exit(config);

  return 0;
}