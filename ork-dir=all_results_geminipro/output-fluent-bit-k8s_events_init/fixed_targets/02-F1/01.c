#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstring>
#include <vector>

#include "flb_input.h"

extern "C" {
#include "k8s_events.h"
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  std::vector<uint8_t> config_data = stream.ConsumeBytes<uint8_t>(size);
  flb_config* config = flb_config_create();
  flb_config_parse(config, reinterpret_cast<char*>(config_data.data()),
                   config_data.size());

  std::vector<uint8_t> instance_data = stream.ConsumeBytes<uint8_t>(size);
  flb_input_instance* instance = flb_input_instance_create(
      reinterpret_cast<char*>(instance_data.data()), instance_data.size());

  std::vector<uint8_t> input_data = stream.ConsumeRemainingBytes();
  char* input = reinterpret_cast<char*>(input_data.data());

  int ret = k8s_events_init(instance, config, input);
  flb_config_destroy(config);
  flb_input_instance_destroy(instance);
  return ret;
}