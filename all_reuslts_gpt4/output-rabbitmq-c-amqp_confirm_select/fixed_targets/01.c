#include <fuzzer/FuzzedDataProvider.h>
#include <cstddef>
#include <cstdint>
#include <amqp_tcp_socket.h>
#include <amqp.h>
#include <amqp_framing.h>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider stream(data, size);

  // Initialize the library
  amqp_connection_state_t conn = amqp_new_connection();

  // Open a socket
  amqp_socket_t *socket = amqp_tcp_socket_new(conn);
  if (!socket) {
    amqp_destroy_connection(conn);
    return 0;
  }

  // Try to open a connection
  int status = amqp_socket_open(socket, "localhost", 5672);
  if (status != AMQP_STATUS_OK) {
    amqp_destroy_connection(conn);
    return 0;
  }

  // Login to the server
  amqp_rpc_reply_t reply = amqp_login(conn, "/", 0, 131072, 0, AMQP_SASL_METHOD_PLAIN, "guest", "guest");
  if (reply.reply_type != AMQP_RESPONSE_NORMAL) {
    amqp_destroy_connection(conn);
    return 0;
  }

  // Open a channel
  amqp_channel_open_ok_t *res = amqp_channel_open(conn, 1);
  if (res == NULL) {
    amqp_destroy_connection(conn);
    return 0;
  }

  // Consume the short channel
  short channel = stream.ConsumeIntegral<short>();

  // Call the target function
  amqp_confirm_select_ok_t_ *confirm_select = amqp_confirm_select(conn, channel);

  // Cleanup
  amqp_destroy_connection(conn);

  return 0;
}