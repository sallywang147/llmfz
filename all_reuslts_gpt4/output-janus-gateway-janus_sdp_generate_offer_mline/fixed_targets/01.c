#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "janus_sdp.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  struct janus_sdp *offer = janus_sdp_new("1.2.3.4", "dummy", JANUS_SDP_OA_AUDIO, "opus", 5004, 1);
  if (offer == nullptr) {
    return 0;
  }

  int ret = janus_sdp_generate_offer_mline(offer);

  janus_sdp_destroy(offer);

  return 0;
}