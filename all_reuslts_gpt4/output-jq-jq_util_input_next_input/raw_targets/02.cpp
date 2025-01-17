#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>

#include "jq.h"
#include "util.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  jq_util_input_state *state = jq_util_input_init(NULL, NULL);
  if (state == NULL) {
    return 0;
  }

  FuzzedDataProvider provider(data, size);
  while (provider.remaining_bytes() > 0) {
    const size_t next_size = provider.ConsumeIntegralInRange<size_t>(
        0,
        provider.remaining_bytes());
    auto next_input = provider.ConsumeBytes<unsigned char>(next_size);
    jq_util_input_add_input(state, (const char *)next_input.data());
    jq_util_input_next_input(state);
  }

  jq_util_input_free(&state);

  return 0;
}