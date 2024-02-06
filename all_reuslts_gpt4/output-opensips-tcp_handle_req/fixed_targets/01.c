#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "tcp_req.h"
#include "tcp_connection.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  struct tcp_req req;
  struct tcp_connection con;

  // Initialize the tcp_req and tcp_connection structures with fuzzed data
  size_t consumed = stream.ConsumeData(&req, sizeof(req));
  if (consumed != sizeof(req)) {
    return 0;
  }

  consumed = stream.ConsumeData(&con, sizeof(con));
  if (consumed != sizeof(con)) {
    return 0;
  }

  // Consume two integers for _max_msg_chunks and _parallel_handling
  int _max_msg_chunks = stream.ConsumeIntegral<int>();
  int _parallel_handling = stream.ConsumeIntegral<int>();

  // Call the function under test
  tcp_handle_req(&req, &con, _max_msg_chunks, _parallel_handling);

  return 0;
}