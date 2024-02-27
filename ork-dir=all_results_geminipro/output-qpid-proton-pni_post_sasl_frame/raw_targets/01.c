#include <fuzzer/FuzzedDataProvider.h>

#include <cstdint>
#include <cstdlib>

#include "proton/pn_transport.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  pn_transport_t *transport =
      static_cast<pn_transport_t *>(malloc(sizeof(pn_transport_t)));
  if (transport == nullptr) {
    return 0;
  }
  pni_post_sasl_frame(transport);
  free(transport);
  return 0;
}