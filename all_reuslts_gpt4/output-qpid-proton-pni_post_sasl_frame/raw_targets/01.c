#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "proton/transport.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  struct pn_transport_t *transport = pn_transport();
  if (!transport) {
    return 0;
  }

  pni_post_sasl_frame(transport);

  pn_transport_free(transport);

  return 0;
}