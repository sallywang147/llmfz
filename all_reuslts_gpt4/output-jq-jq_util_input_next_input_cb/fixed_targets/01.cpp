#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "jq.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  static bool initialized = false;
  if (!initialized) {
    jq_init();
    initialized = true;
  }

  jq_state* jq = jq_init();
  if (jq == nullptr) {
    return 0;
  }

  FuzzedDataProvider provider(data, size);
  std::string input_data = provider.ConsumeRemainingBytesAsString();
  jq_util_input_next_input_cb(jq, input_data.c_str());

  jq_teardown(&jq);

  return 0;
}