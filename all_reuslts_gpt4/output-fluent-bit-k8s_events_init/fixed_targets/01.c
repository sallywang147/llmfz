#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "fluent-bit/flb_input.h"
#include "fluent-bit/flb_config.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  // Initialize the Fluent Bit input instance and configuration.
  struct flb_input_instance *ins = flb_input_new();
  struct flb_config *config = flb_config_init();

  // Consume the remaining bytes as a string for the data parameter.
  std::string data_str = stream.ConsumeRemainingBytesAsString();
  char* data_cstr = data_str.c_str();

  // Call the function under test.
  int result = k8s_events_init(ins, config, data_cstr);

  // Cleanup.
  flb_input_exit(ins);
  flb_config_exit(config);

  return 0;
}