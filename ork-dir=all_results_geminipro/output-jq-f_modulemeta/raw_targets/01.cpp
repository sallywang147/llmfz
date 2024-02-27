#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <string>

#include "jv.h"
#include "jq_parser.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  const std::string jq_string = stream.ConsumeRemainingBytesAsString();
  jq_state *jq = jq_init();
  if (jq == nullptr) {
    return 0;
  }

  jv_refcnt *refcnt = jv_refcnt_create(jv_string(jq_string.c_str()), 1);
  f_modulemeta(jq, 0, refcnt);
  jv_free(jv_refcnt_dec(refcnt, 1));
  jq_teardown(&jq);
  return 0;
}