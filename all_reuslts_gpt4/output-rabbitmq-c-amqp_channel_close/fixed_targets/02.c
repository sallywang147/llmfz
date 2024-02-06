#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "amqp.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider provider(data, size);

  amqp_rpc_reply_t state;
  amqp_connection_state_t channel;
  short code = provider.ConsumeIntegral<short>();
  int i = provider.ConsumeIntegral<int>();

  amqp_channel_close(&state, &channel, code, i);

  return 0;
}