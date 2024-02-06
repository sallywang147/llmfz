#include "ntpd.h"
#include <fuzzer/FuzzedDataProvider.h>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider stream(data, size);

  struct peer peer;

  // Initialize the peer struct with random data
  peer.nts_state.aead = stream.ConsumeIntegral<int>();
  peer.nts_state.cookielen = stream.ConsumeIntegral<size_t>();
  peer.nts_state.writeIdx = stream.ConsumeIntegral<int>();
  peer.nts_state.count = stream.ConsumeIntegral<int>();

  peer.srcadr.sa4.sin_family = stream.ConsumeIntegral<sa_family_t>();
  peer.srcadr.sa4.sin_port = stream.ConsumeIntegral<in_port_t>();
  peer.srcadr.sa4.sin_addr.s_addr = stream.ConsumeIntegral<in_addr_t>();

  // Call the function to fuzz
  nts_probe(&peer);

  return 0;
}