#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <string>

#include "jq.h"

extern "C" {
#include "jq_module_meta.h"
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  const std::string mod_relpath = stream.ConsumeRemainingBytesAsString();
  jq_state *jq = jq_init();
  load_module_meta(jq, mod_relpath.size(), nullptr);
  jq_teardown(&jq);
  return 0;
}