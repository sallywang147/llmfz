#include <fuzzer/FuzzedDataProvider.h>
#include "../net/tcp_conn.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  if (size < sizeof(struct tcp_connection)) {
    return 0;
  }

  FuzzedDataProvider stream(data, size);

  struct tcp_connection con;
  size_t consumed = stream.ConsumeData(&con, sizeof(con));
  if (consumed != sizeof(con)) {
    return 0;
  }

  int bytes_read = stream.ConsumeIntegral<int>();

  tcp_read_req(&con, &bytes_read);

  return 0;
}