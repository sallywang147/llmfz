#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <cstring>
#include <string>

#include "tcp.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  const uint8_t buf_size = stream.ConsumeIntegral<uint8_t>();
  char buf[buf_size];
  const uint8_t bytes_read = stream.ConsumeIntegral<uint8_t>();
  struct tcp_connection con = {0};
  con.rbuf = buf;
  con.rbuf_size = buf_size;
  con.rbytes = bytes_read;
  tcp_read_req(&con, nullptr);
  return 0;
}