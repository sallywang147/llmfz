#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>

#include "jq.h"
#include "jv.h"
#include "jq_util_input.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  jq_state *jq = jq_init();
  if (jq == NULL) {
    return 0;
  }

  FuzzedDataProvider provider(data, size);
  std::string str = provider.ConsumeRemainingBytesAsString();
  char *input = const_cast<char*>(str.c_str());

  jq_util_input_next_input_cb(jq, input);

  jq_teardown(&jq);

  return 0;
}