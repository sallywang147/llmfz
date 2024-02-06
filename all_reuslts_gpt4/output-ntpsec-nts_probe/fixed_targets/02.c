#include "ntpd.h"
#include <fuzzer/FuzzedDataProvider.h>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider stream(data, size);
  struct peer peer;

  // Initialize the peer struct
  peer.nts_state.aead = stream.ConsumeIntegral<uint16_t>();
  peer.nts_state.cookielen = stream.ConsumeIntegral<size_t>();
  peer.nts_state.writeIdx = stream.ConsumeIntegral<int>();
  peer.nts_state.count = stream.ConsumeIntegral<int>();

  // Call the function to fuzz
  nts_probe(&peer);

  return 0;
}