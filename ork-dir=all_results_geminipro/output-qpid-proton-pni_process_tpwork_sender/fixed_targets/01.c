#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "pni_transport.h"

extern "C" {
#include "proton/message.h"
#include "proton/transport.h"
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  pn_transport_t* transport = pn_transport();
  pn_delivery_t* delivery = pn_delivery(transport);
  std::vector<uint8_t> payload = stream.ConsumeRemainingBytes<uint8_t>();
  int ret = pni_process_tpwork_sender(transport, delivery,
                                      reinterpret_cast<char*>(payload.data()),
                                      payload.size(), payload.size());
  pn_transport_free(transport);
  pn_delivery_free(delivery);
  return ret;
}