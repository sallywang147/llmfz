#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "open62541.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  // Consume data for json_config
  size_t json_config = stream.ConsumeIntegral<size_t>();

  // Consume data for filename
  std::string filename = stream.ConsumeRemainingBytesAsString();

  // Call the function to fuzz
  struct UA_Server *server = UA_Server_newFromFile(json_config, const_cast<char*>(filename.c_str()));

  // Cleanup
  if (server != nullptr) {
    UA_Server_delete(server);
  }

  return 0;
}