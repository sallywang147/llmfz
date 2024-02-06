#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <string>

#include "tcp_connection.h"

extern "C" {
#include "tcp_connection.h"
}

// Declare the function `tcp_read_req` in the header file `tcp_connection.h`.
int tcp_read_req(struct tcp_connection* con, int* bytes_read);

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  struct tcp_connection con;
  int bytes_read;
  tcp_read_req(&con, &bytes_read);
  return 0;
}