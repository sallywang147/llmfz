#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <string>

#include "mongoose.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  struct mg_connection *conn = nullptr;
  char *path = stream.ConsumeRemainingBytesAsString().c_str();
  char *mime_type = stream.ConsumeRemainingBytesAsString().c_str();
  mg_send_mime_file(conn, path, mime_type);
  return 0;
}