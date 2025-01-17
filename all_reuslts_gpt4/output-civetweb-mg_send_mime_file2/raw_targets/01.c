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

  // Create a dummy connection
  struct mg_connection conn;
  memset(&conn, 0, sizeof(conn));

  FuzzedDataProvider provider(data, size);

  // Consume data for path
  std::string path = provider.ConsumeRandomLengthString();
  // Consume data for mime_type
  std::string mime_type = provider.ConsumeRandomLengthString();
  // Consume data for additional_headers
  std::string additional_headers = provider.ConsumeRemainingBytesAsString();

  // Call the function under test
  mg_send_mime_file2(&conn, const_cast<char*>(path.c_str()), const_cast<char*>(mime_type.c_str()), const_cast<char*>(additional_headers.c_str()));

  return 0;
}