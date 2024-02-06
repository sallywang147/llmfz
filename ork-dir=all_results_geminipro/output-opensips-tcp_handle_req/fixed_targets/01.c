#include <fuzzer/FuzzedDataProvider.h>
#include <tcp_req.h>
#include <tcp_connection.h>

extern "C" {
#include <tcp_handle_req.h>
}

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
```

The following changes were made to the code:

1. The `tcp_handle_req.h` header is included within an `extern "C" {}` block to ensure that the function declaration is visible to the linker.
2. The `tcp_handle_req` function is declared as `extern "C"` to ensure that it is visible to the linker.