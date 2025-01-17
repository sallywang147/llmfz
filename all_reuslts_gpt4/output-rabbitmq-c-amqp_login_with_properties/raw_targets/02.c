#include <fuzzer/FuzzedDataProvider.h>
#include <rabbitmq-c/amqp.h>
#include <rabbitmq-c/tcp_socket.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider fuzzed_data(data, size);

  // Initialize the connection state
  amqp_connection_state_t conn = amqp_new_connection();
  if (!conn) {
    return 0;
  }

  // Create a TCP socket
  amqp_socket_t *socket = amqp_tcp_socket_new(conn);
  if (!socket) {
    amqp_destroy_connection(conn);
    return 0;
  }

  // Open the socket
  if (amqp_socket_open(socket, "localhost", 5672)) {
    amqp_destroy_connection(conn);
    return 0;
  }

  // Initialize the login parameters
  struct amqp_rpc_reply_t_ state;
  char *channel_max = fuzzed_data.ConsumeBytesAsString(fuzzed_data.ConsumeIntegralInRange<size_t>(0, 10)).c_str();
  int frame_max = fuzzed_data.ConsumeIntegral<int>();
  int heartbeat = fuzzed_data.ConsumeIntegral<int>();
  int client_properties = fuzzed_data.ConsumeIntegral<int>();
  struct amqp_table_t_ sasl_method;
  int sasl_method_entries = fuzzed_data.ConsumeIntegralInRange<int>(0, 10);
  sasl_method.num_entries = sasl_method_entries;
  sasl_method.entries = new amqp_table_entry_t[sasl_method_entries];
  for (int i = 0; i < sasl_method_entries; i++) {
    sasl_method.entries[i].key = amqp_cstring_bytes(fuzzed_data.ConsumeBytesAsString(fuzzed_data.ConsumeIntegralInRange<size_t>(0, 10)).c_str());
    sasl_method.entries[i].value.kind = AMQP_FIELD_KIND_UTF8;
    sasl_method.entries[i].value.value.bytes = amqp_cstring_bytes(fuzzed_data.ConsumeBytesAsString(fuzzed_data.ConsumeIntegralInRange<size_t>(0, 10)).c_str());
  }

  // Call the function to fuzz
  amqp_login_with_properties(&state, conn, channel_max, frame_max, heartbeat, client_properties, &sasl_method, fuzzed_data.ConsumeIntegral<int>());

  // Clean up
  delete[] sasl_method.entries;
  amqp_destroy_connection(conn);

  return 0;
}