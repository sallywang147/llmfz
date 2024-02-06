#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>

#include "open62541.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  // Initialize the server
  UA_Server *server = UA_Server_new();
  if (!server) {
    return 0;
  }

  // Fuzzing code goes here

  // Cleanup and delete the server
  UA_Server_delete(server);

  return 0;
}