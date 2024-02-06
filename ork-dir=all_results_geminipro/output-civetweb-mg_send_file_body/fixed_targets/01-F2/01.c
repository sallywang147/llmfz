#include <fuzzer/FuzzedDataProvider.h>
#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <string>

extern "C" {
#include "mongoose.h"
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  const int send_buffer_size = stream.ConsumeIntegral<int>();
  const std::string path = stream.ConsumeRemainingBytesAsString();

  struct mg_connection conn;
  memset(&conn, 0, sizeof(conn));
  conn.send_iov = static_cast<struct mg_iovec*>(
      malloc(sizeof(struct mg_iovec) * send_buffer_size));
  conn.send_iov_count = send_buffer_size;

  mg_send_file_body(&conn, path.c_str());  // Fix: Remove const_cast
  free(conn.send_iov);
  return 0;
}
```

Changes:
1. Remove `const_cast` from `mg_send_file_body` function call.
2. Include `mongoose.h` with `extern "C" {}` to resolve the linker error.