#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <string>
#include <vector>

#include "mongoose.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  const std::string path = stream.ConsumeRemainingBytesAsString();

  struct mg_connection conn;
  memset(&conn, 0, sizeof(conn));
  int result = mg_send_file_body(&conn, const_cast<char*>(path.c_str()));
  return result;
}