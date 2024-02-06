#include <fuzzer/FuzzedDataProvider.h>
#include <cstddef>
#include <cstdint>
#include <amqp.h>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider stream(data, size);

  // Initialize the amqp connection state
  amqp_connection_state_t state = amqp_new_connection();

  // Consume the data to get the channel
  short channel = stream.ConsumeIntegral<short>();

  // Call the function under test
  struct amqp_confirm_select_ok_t_ * result = amqp_confirm_select(state, channel);

  // Cleanup
  amqp_destroy_connection(state);

  return 0;
}