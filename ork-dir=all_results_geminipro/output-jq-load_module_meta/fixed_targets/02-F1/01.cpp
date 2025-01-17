#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <string>

extern "C" {
#include "jq.h"
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  struct jq_state * jq = jq_init();
  if (jq == nullptr) {
    return 0;
  }

  const size_t mod_relpath = stream.ConsumeIntegral<size_t>();
  struct jv_refcnt * jv_refcnt = nullptr;
  load_module_meta(jq, mod_relpath, jv_refcnt);
  jq_teardown(&jq);
  return 0;
}