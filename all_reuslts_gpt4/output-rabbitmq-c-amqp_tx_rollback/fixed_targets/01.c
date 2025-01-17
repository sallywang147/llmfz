#include <fuzzer/FuzzedDataProvider.h>
#include <cstddef>
#include <cstdint>
#include <amqp.h>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider stream(data, size);

  // Initialize the AMQP connection state
  amqp_connection_state_t state = amqp_new_connection();

  // Extract a short from the fuzzed data
  short channel = stream.ConsumeIntegral<short>();

  // Call the function to fuzz
  amqp_tx_rollback(state, channel);

  // Clean up
  amqp_destroy_connection(state);

  return 0;
}