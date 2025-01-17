#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "amqp.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider provider(data, size);
  struct amqp_connection_state_t_ * state = amqp_new_connection();
  short channel = provider.ConsumeIntegral<short>();

  struct amqp_confirm_select_ok_t_ * result = amqp_tx_rollback(state, channel);

  amqp_destroy_connection(state);

  return 0;
}