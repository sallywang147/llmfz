#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <string>

#include "flb.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  struct flb_config config;
  struct flb_cf cf;

  std::string config_string = stream.ConsumeRemainingBytesAsString();
  flb_config_init(&config);
  int ret = flb_config_load_config_format(&config, &cf, config_string.c_str());
  flb_config_destroy(&config);
  return ret;
}