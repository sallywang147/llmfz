#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "jq.h"
#include "jv.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  if (size < 2) {
    return 0;
  }

  FuzzedDataProvider stream(data, size);

  // Initialize jq state
  jq_state *jq = jq_init();
  if (jq == nullptr) {
    return 0;
  }

  // Consume data for size_t x
  size_t x = stream.ConsumeIntegral<size_t>();

  // Create jv_refcnt *y
  jv_refcnt *y = (jv_refcnt*)malloc(sizeof(jv_refcnt));
  if (y == nullptr) {
    jq_teardown(&jq);
    return 0;
  }
  y->cnt = stream.ConsumeIntegral<int>();

  // Consume data for size_t
  size_t size_t_val = stream.ConsumeIntegral<size_t>();

  // Create jv_refcnt *
  jv_refcnt *jv_refcnt_ptr = (jv_refcnt*)malloc(sizeof(jv_refcnt));
  if (jv_refcnt_ptr == nullptr) {
    free(y);
    jq_teardown(&jq);
    return 0;
  }
  jv_refcnt_ptr->cnt = stream.ConsumeIntegral<int>();

  // Call the target function
  f_min_by_impl(jq, x, y, size_t_val, jv_refcnt_ptr);

  // Clean up
  free(jv_refcnt_ptr);
  free(y);
  jq_teardown(&jq);

  return 0;
}