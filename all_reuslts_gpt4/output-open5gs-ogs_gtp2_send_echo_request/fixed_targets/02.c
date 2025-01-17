#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "ogs_gtp.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  // Initialize the gtp node
  struct ogs_gtp_node_s gnode;
  memset(&gnode, 0, sizeof(gnode));

  // Consume data for recovery and features
  char recovery = stream.ConsumeIntegral<char>();
  char features = stream.ConsumeIntegral<char>();

  // Call the function to be fuzzed
  ogs_gtp2_send_echo_request(&gnode, recovery, features);

  return 0;
}