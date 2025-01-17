#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "proton/pn_transport.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  // We need to initialize the Proton library.
  pn_transport_t *transport = pn_transport();
  if (!transport) {
    return 0;
  }

  // Create a delivery object.
  pn_delivery_t *delivery = pn_delivery(pn_link_head(pn_session_link_head(pn_connection_session_head(pn_transport_connection(transport)), 0), 0), pn_dtag("tag", 3));
  if (!delivery) {
    pn_transport_free(transport);
    return 0;
  }

  // Consume the remaining bytes as a string.
  std::string str = stream.ConsumeRemainingBytesAsString();
  char *ptr = const_cast<char*>(str.c_str());

  // Call the function under test.
  int result = pni_process_tpwork_sender(transport, delivery, ptr);

  // Clean up.
  pn_delivery_free(delivery);
  pn_transport_free(transport);

  return 0;
}