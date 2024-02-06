#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "mongoose.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  // Create a mongoose connection
  struct mg_connection *conn;
  conn = mg_connect("localhost", 8080);
  if (conn == NULL) {
    return 0;
  }

  // Extract a string for the file path
  std::string path_str = stream.ConsumeRandomLengthString();
  char *path = const_cast<char *>(path_str.c_str());

  // Call the function to be fuzzed
  mg_send_file_body(conn, path);

  // Close the connection
  mg_close_connection(conn);

  return 0;
}