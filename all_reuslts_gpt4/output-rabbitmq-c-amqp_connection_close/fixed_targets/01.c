#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>

#include "amqp.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  struct amqp_rpc_reply_t_ state;
  struct amqp_connection_state_t_ code;

  int int_arg = stream.ConsumeIntegral<int>();

  amqp_connection_close(&state, &code, int_arg);

  return 0;
}