#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>

#include "jv.h"
#include "jq_parser.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  jq_state* jq = jq_init();
  if (jq == nullptr) {
    return 0;
  }

  const size_t a = stream.ConsumeIntegral<size_t>();
  const struct jv_refcnt* b =
      reinterpret_cast<struct jv_refcnt*>(stream.ConsumeBytes<uint8_t>(size));

  f_modulemeta(jq, a, b);

  jq_teardown(&jq);
  return 0;
}