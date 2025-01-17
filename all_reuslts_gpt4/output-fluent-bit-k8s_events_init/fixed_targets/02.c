#include <fuzzer/FuzzedDataProvider.h>
#include <fluent-bit/flb_input.h>
#include <fluent-bit/flb_config.h>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider provider(data, size);

  // Create a Fluent Bit context
  struct flb_config *config = flb_config_init();
  if (!config) {
    return 0;
  }

  // Create a Fluent Bit input instance
  struct flb_input_instance *ins = flb_input_new(config, "k8s_events", NULL, true);
  if (!ins) {
    flb_config_exit(config);
    return 0;
  }

  // Consume the data as a string for the third parameter of k8s_events_init
  std::string data_str = provider.ConsumeRemainingBytesAsString();
  char *data_cstr = const_cast<char*>(data_str.c_str());

  // Call the function to be fuzzed
  k8s_events_init(ins, config, data_cstr);

  // Cleanup
  flb_input_instance_destroy(ins);
  flb_config_exit(config);

  return 0;
}