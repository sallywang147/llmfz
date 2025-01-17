#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <string>

#include "janus_sdp.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  std::string name = stream.ConsumeRandomLengthString();
  std::string address = stream.ConsumeRemainingBytesAsString();

  struct janus_sdp *sdp_offer = janus_sdp_generate_offer(const_cast<char*>(name.c_str()), const_cast<char*>(address.c_str()));

  if (sdp_offer) {
    janus_sdp_destroy(sdp_offer);
  }

  return 0;
}