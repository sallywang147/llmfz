#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>

#include "ogs-gtp.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  // Create a gtp_node_s structure
  struct ogs_gtp_node_s gnode;

  // Consume data for the structure
  size_t consumed = stream.ConsumeData(&gnode, sizeof(gnode));
  if (consumed != sizeof(gnode)) {
    return 0;
  }

  // Consume data for the recovery and features parameters
  char recovery = stream.ConsumeIntegral<char>();
  char features = stream.ConsumeIntegral<char>();

  // Call the function to fuzz
  ogs_gtp2_send_echo_request(&gnode, recovery, features);

  return 0;
}