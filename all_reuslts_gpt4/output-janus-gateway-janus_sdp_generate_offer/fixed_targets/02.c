#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "janus_sdp.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  std::string name = stream.ConsumeBytesAsString(stream.remaining_bytes() / 2);
  std::string address = stream.ConsumeRemainingBytesAsString();

  struct janus_sdp *sdp = janus_sdp_generate_offer(const_cast<char*>(name.c_str()), const_cast<char*>(address.c_str()));

  if(sdp != nullptr) {
    janus_sdp_destroy(sdp);
  }

  return 0;
}