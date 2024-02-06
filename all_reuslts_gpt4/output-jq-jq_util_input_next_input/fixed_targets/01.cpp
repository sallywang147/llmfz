#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>

#include "jq.h"
#include "util.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  // Initialize jq_util_input_state
  jq_util_input_state state;
  state.jq = NULL;
  state.input_cb = NULL;
  state.input_cb_data = NULL;
  state.current_input = NULL;
  state.next_input_idx = 0;
  state.inputs = NULL;
  state.ninputs = 0;
  state.no_free = 0;
  state.dumpopts = 0;
  state.parser = NULL;

  // Call the function under test
  jq_util_input_next_input(&state);

  return 0;
}