#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <cstring>

extern "C" {
#include "jq_util.h"
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  struct jq_util_input_state state;
  memset(&state, 0, sizeof(state));
  state.data = stream.ConsumeRemainingBytes();
  state.len = state.data.size();
  jq_util_input_next_input(&state);
  jq_util_input_free(&state);  // Free the allocated memory.
  return 0;
}