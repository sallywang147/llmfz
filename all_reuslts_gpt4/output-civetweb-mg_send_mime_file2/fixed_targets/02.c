#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "mongoose.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  static bool initialized = false;
  if (!initialized) {
    mg_init_library(0);
    initialized = true;
  }

  FuzzedDataProvider provider(data, size);

  struct mg_server *server = mg_create_server(NULL, NULL);
  struct mg_connection *conn = mg_connect(server, "localhost");

  if (conn == NULL) {
    mg_destroy_server(&server);
    return 0;
  }

  // Consume data for path, mime_type, and additional_headers
  std::string path = provider.ConsumeRandomLengthString();
  std::string mime_type = provider.ConsumeRandomLengthString();
  std::string additional_headers = provider.ConsumeRandomLengthString();

  // Call the function under test
  mg_send_mime_file2(conn, const_cast<char*>(path.c_str()), const_cast<char*>(mime_type.c_str()), const_cast<char*>(additional_headers.c_str()));

  mg_close_connection(conn);
  mg_destroy_server(&server);

  return 0;
}