#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <string>

#include "hostapd.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  const std::string config_file = stream.ConsumeRemainingBytesAsString();

  struct hostapd_iface iface;
  iface.config_fname = config_file.c_str();
  hostapd_reload_config(&iface);
  return 0;
}