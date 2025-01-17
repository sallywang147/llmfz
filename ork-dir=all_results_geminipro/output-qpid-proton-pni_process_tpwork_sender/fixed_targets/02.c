#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <cstring>

#include "proton/pn.h"
#include "proton/pni.h"

extern "C" {
#include "proton/pn_transport.h"
#include "proton/pn_delivery.h"
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  pn_transport_t* transport = pn_transport();
  if (transport == nullptr) {
    return 0;
  }

  pn_delivery_t* delivery = pn_delivery(transport);
  if (delivery == nullptr) {
    pn_free(transport);
    return 0;
  }

  const size_t payload_size = stream.ConsumeIntegralInRange<size_t>(0, size);
  char* payload = stream.ConsumeBytes<char>(payload_size);

  int result = pni_process_tpwork_sender(transport, delivery, payload, payload_size, payload_size);

  pn_free(transport);
  pn_free(delivery);
  return result;
}