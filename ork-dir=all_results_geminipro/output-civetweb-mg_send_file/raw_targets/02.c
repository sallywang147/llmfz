#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <string>

#include "mongoose.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  const size_t path_length = stream.ConsumeIntegralInRange<size_t>(0, 1024);
  char* path = new char[path_length + 1];
  stream.ConsumeBytes(path, path_length);
  path[path_length] = '\0';

  struct mg_connection conn;
  mg_send_file(&conn, path);
  delete[] path;
  return 0;
}