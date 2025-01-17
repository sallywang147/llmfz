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
  struct mg_connection* conn = reinterpret_cast<struct mg_connection*>(
      stream.ConsumeIntegral<size_t>());
  struct mg_http_message* http_message = reinterpret_cast<struct mg_http_message*>(
      stream.ConsumeIntegral<size_t>());
  std::string format = stream.ConsumeRemainingBytesAsString();
  mg_ws_upgrade(conn, http_message, format.c_str());
  return 0;
}