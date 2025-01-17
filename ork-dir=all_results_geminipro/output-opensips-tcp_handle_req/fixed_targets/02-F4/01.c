#include <fuzzer/FuzzedDataProvider.h>

#include <cstdint>
#include <cstdlib>
#include <cstring>
#include <string>

extern "C" {
#include "tcp_handle_req.h"
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  const uint8_t max_msg_chunks = stream.ConsumeIntegral<uint8_t>();
  const uint8_t parallel_handling = stream.ConsumeIntegral<uint8_t>();
  const std::string req_data = stream.ConsumeRemainingBytesAsString();
  struct tcp_req req;
  memset(&req, 0, sizeof(req));
  req.buf = const_cast<char*>(req_data.c_str());
  req.len = req_data.length();
  struct tcp_connection con;
  memset(&con, 0, sizeof(con));
  con.fd = -1;
  tcp_handle_req(&req, &con, max_msg_chunks, parallel_handling);
  return 0;
}