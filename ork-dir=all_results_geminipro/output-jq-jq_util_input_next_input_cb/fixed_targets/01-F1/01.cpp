#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <string>

#include "jq.h"

extern "C" {
#include "jq.h"
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  const std::string input = stream.ConsumeRemainingBytesAsString();
  struct jq_state *jq = jq_init();
  jq_util_input_next_input_cb(jq, const_cast<char *>(input.c_str()));
  jq_teardown(&jq);
  return 0;
}