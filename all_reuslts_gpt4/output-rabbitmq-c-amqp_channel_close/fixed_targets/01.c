#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "amqp.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider stream(data, size);

  // Initialize the AMQP connection state
  struct amqp_connection_state_t_ *conn = amqp_new_connection();
  if (conn == nullptr) {
    return 0;
  }

  // Initialize the AMQP RPC reply state
  struct amqp_rpc_reply_t_ reply;

  // Consume data from the fuzzer input
  short code = stream.ConsumeIntegral<short>();
  int dummy = stream.ConsumeIntegral<int>();

  // Call the function to be fuzzed
  amqp_channel_close(&reply, conn, code, dummy);

  // Clean up
  amqp_destroy_connection(conn);

  return 0;
}