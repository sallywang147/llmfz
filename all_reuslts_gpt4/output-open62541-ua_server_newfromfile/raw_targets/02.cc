#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "open62541/server.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  size_t json_config = stream.ConsumeIntegral<size_t>();
  std::string file_path = stream.ConsumeRemainingBytesAsString();

  // Save the file path string to a temporary file
  FILE *tmpf = tmpfile();
  fwrite(file_path.c_str(), 1, file_path.size(), tmpf);
  fflush(tmpf);
  rewind(tmpf);

  // Get the temporary file name
  char path[256];
  snprintf(path, sizeof(path), "/proc/self/fd/%d", fileno(tmpf));

  struct UA_Server* server = UA_Server_newFromFile(json_config, path);

  // Clean up
  if (server) {
    UA_Server_delete(server);
  }
  fclose(tmpf);

  return 0;
}