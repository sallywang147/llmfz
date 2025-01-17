#include <fuzzer/FuzzedDataProvider.h>
#include <cstddef>
#include <cstdint>
#include <amqp.h>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider stream(data, size);

  // Initialize the connection state
  struct amqp_connection_state_t_ *vhost = amqp_new_connection();

  // Initialize the rpc reply
  struct amqp_rpc_reply_t_ state;

  // Consume data for the parameters
  char *channel_max = const_cast<char *>(stream.ConsumeBytesAsString(stream.remaining_bytes()/4).c_str());
  int frame_max = stream.ConsumeIntegral<int>();
  int heartbeat = stream.ConsumeIntegral<int>();
  int client_properties = stream.ConsumeIntegral<int>();
  
  // Initialize the SASL method table
  struct amqp_table_t_ sasl_method;
  sasl_method.num_entries = 0;
  sasl_method.entries = nullptr;

  // Consume data for the last parameter
  int last_param = stream.ConsumeIntegral<int>();

  // Call the function under test
  amqp_login_with_properties(&state, vhost, channel_max, frame_max, heartbeat, client_properties, &sasl_method, last_param);

  // Cleanup
  amqp_destroy_connection(vhost);

  return 0;
}