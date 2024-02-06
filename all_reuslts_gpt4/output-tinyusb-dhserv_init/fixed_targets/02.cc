#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <vector>

#include "dhcp.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  // Define and initialize the dhcp_config struct
  struct dhcp_config config;
  config.verbose = stream.ConsumeBool();
  config.interface = stream.ConsumeBytesAsString(stream.remaining_bytes()).c_str();
  
  // Call the function to fuzz
  dhserv_init(&config);

  return 0;
}