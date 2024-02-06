#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <string>

#include "tcp_req.h"
#include "tcp_connection.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  const uint8_t max_msg_chunks = stream.ConsumeIntegral<uint8_t>();
  const uint8_t parallel_handling = stream.ConsumeIntegral<uint8_t>();
  const std::string req_data = stream.ConsumeRemainingBytesAsString();

  struct tcp_req req;
  req.data = reinterpret_cast<uint8_t*>(const_cast<char*>(req_data.c_str()));
  req.len = req_data.size();

  struct tcp_connection con;
  con.rbuf_size = 0;
  con.rbuf = nullptr;
  con.wbuf_size = 0;
  con.wbuf = nullptr;
  con.wbuf_offset = 0;

  tcp_handle_req(&req, &con, max_msg_chunks, parallel_handling);
  return 0;
}