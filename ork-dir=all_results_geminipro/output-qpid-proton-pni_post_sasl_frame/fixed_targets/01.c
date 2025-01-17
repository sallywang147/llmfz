#include <fuzzer/FuzzedDataProvider.h>

#include <cstdint>
#include <cstdlib>

extern "C" {
#include "proton/pn_transport.h"
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  pn_transport_t *transport =
      static_cast<pn_transport_t *>(malloc(sizeof(pn_transport_t)));
  if (transport == nullptr) {
    return 0;
  }
  pn_transport_init(transport, nullptr);
  pn_transport_bind(transport, nullptr);
  pni_post_sasl_frame(transport);
  pn_transport_unbind(transport);
  pn_transport_free(transport);
  return 0;
}