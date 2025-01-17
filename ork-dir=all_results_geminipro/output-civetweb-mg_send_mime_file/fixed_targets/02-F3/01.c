#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <string>

#include "mongoose.h"

extern "C" {
#include "mongoose.h"
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  struct mg_connection *conn = mg_create_connection();
  char *path = stream.ConsumeString().c_str();
  char *mime_type = stream.ConsumeString().c_str();
  mg_send_mime_file(conn, path, mime_type);
  mg_close_connection(conn);
  return 0;
}