#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <cstring>
#include <string>
#include <vector>

#include "mongoose.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  struct mg_connection connection;
  memset(&connection, 0, sizeof(connection));

  struct mg_http_message http_message;
  memset(&http_message, 0, sizeof(http_message));

  const size_t fmt_size = stream.ConsumeIntegralInRange<size_t>(0, 1024);
  std::vector<char> fmt_buffer(fmt_size);
  stream.ConsumeBytes<char>(fmt_buffer.data(), fmt_size);

  mg_ws_upgrade(&connection, &http_message, fmt_buffer.data());
  return 0;
}