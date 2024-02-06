#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "sdp.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  // Initialize janus_sdp objects
  struct janus_sdp *offer = janus_sdp_create("1.0", "fuzzer", "1", "IN", "IP4", "127.0.0.1");
  struct janus_sdp *answer = janus_sdp_create("1.0", "fuzzer", "1", "IN", "IP4", "127.0.0.1");
  struct janus_sdp_mline *offered = (struct janus_sdp_mline *)malloc(sizeof(struct janus_sdp_mline));

  // Check if allocation was successful
  if(offer == NULL || answer == NULL || offered == NULL) {
    return 0;
  }

  // Fill the mline structure with data
  offered->type = stream.ConsumeEnum<janus_sdp_mtype>();
  offered->port = stream.ConsumeIntegralInRange<uint16_t>(0, 65535);
  offered->proto = stream.ConsumeRandomLengthString().c_str();
  offered->direction = stream.ConsumeEnum<janus_sdp_mdirection>();

  // Call the function under test
  int ret = janus_sdp_generate_answer_mline(offer, answer, offered);

  // Clean up
  janus_sdp_destroy(offer);
  janus_sdp_destroy(answer);
  free(offered);

  return 0;
}