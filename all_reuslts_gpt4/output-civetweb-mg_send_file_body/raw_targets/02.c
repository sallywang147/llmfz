#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <vector>

#include "mongoose.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  if (size == 0) {
    return 0;
  }

  FuzzedDataProvider stream(data, size);

  // Create a connection
  struct mg_connection *conn = mg_connect(NULL, "localhost:8080");
  if (conn == NULL) {
    return 0;
  }

  // Extract a string for the file path
  std::string filePath = stream.ConsumeRemainingBytesAsString();
  char* path = strdup(filePath.c_str());

  // Call the function to fuzz
  mg_send_file_body(conn, path);

  // Cleanup
  free(path);
  mg_close_connection(conn);

  return 0;
}