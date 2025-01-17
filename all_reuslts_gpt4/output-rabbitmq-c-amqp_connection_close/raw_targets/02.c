#include <fuzzer/FuzzedDataProvider.h>
#include <cstddef>
#include <cstdint>
#include <amqp.h>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider stream(data, size);

  // Initialize the connection state
  amqp_connection_state_t conn = amqp_new_connection();
  if (conn == NULL) {
    return 0;
  }

  // Initialize the RPC reply
  amqp_rpc_reply_t reply;
  reply.reply_type = AMQP_RESPONSE_NORMAL;

  // Consume the remaining data as an integer
  int close_code = stream.ConsumeIntegral<int>();

  // Call the target function
  amqp_connection_close(&reply, conn, close_code);

  // Clean up
  amqp_destroy_connection(conn);

  return 0;
}