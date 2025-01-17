#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>

#include "jv.h"
#include "jq_parser.h"

extern "C" {
#include "jq.h"
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  jq_state* jq = jq_init();
  jv x = jv_array();
  jv y = jv_array();
  for (size_t i = 0; i < stream.ConsumeIntegralInRange<size_t>(0, 100); ++i) {
    jv_array_append(&x, jv_number(stream.ConsumeIntegral<double>()));
    jv_array_append(&y, jv_number(stream.ConsumeIntegral<double>()));
  }
  jv result = f_min_by_impl(jq, x.u.array.size, y.u.array.ptr, y.u.array.size, nullptr);
  jv_free(x);
  jv_free(y);
  jv_free(result);
  jq_teardown(&jq);
  return 0;
}