#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "jq.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  struct jq_state *jq = jq_init();
  if (jq == NULL) {
    return 0;
  }

  FuzzedDataProvider stream(data, size);

  size_t mod_relpath = stream.ConsumeIntegral<size_t>();
  struct jv_refcnt *refcnt = NULL;

  load_module_meta(jq, mod_relpath, refcnt);

  jq_teardown(&jq);

  return 0;
}