#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <string>

#include "flb.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  struct flb_input_instance ins;
  struct flb_config config;

  const std::string config_string = stream.ConsumeRemainingBytesAsString();
  char* config_data = const_cast<char*>(config_string.c_str());

  int ret = k8s_events_init(&ins, &config, config_data);
  if (ret == 0) {
    k8s_events_finish(&ins);
  }

  return 0;
}