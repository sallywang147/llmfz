#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <string>

#include "proton/pn_transport.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  struct pn_transport_t* transport = pn_transport();
  pn_transport_bind(transport, stream.ConsumeBytesAsString().c_str());
  pni_post_sasl_frame(transport);
  pn_transport_unbind(transport, stream.ConsumeBytesAsString().c_str());
  pn_free(transport);
  return 0;
}