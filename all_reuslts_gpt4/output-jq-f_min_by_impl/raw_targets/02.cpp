#include <fuzzer/FuzzedDataProvider.h>
#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "jq.h"
#include "jv.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  // Initialize jq state
  jq_state *jq = jq_init();
  if (jq == nullptr) {
    return 0;
  }

  // Generate size_t parameters
  size_t x = stream.ConsumeIntegral<size_t>();
  size_t z = stream.ConsumeIntegral<size_t>();

  // Generate jv_refcnt parameters
  jv_refcnt* y = (jv_refcnt*) malloc(sizeof(jv_refcnt));
  if (y == nullptr) {
    jq_teardown(&jq);
    return 0;
  }
  y->n = 1;

  jv_refcnt* w = (jv_refcnt*) malloc(sizeof(jv_refcnt));
  if (w == nullptr) {
    free(y);
    jq_teardown(&jq);
    return 0;
  }
  w->n = 1;

  // Call the target function
  f_min_by_impl(jq, x, y, z, w);

  // Cleanup
  free(y);
  free(w);
  jq_teardown(&jq);

  return 0;
}