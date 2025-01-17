#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "janus_sdp.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  // Initialize the janus_sdp structures
  struct janus_sdp offer;
  struct janus_sdp answer;
  struct janus_sdp_mline offered;

  // Consume data for the offer
  offer.name = stream.ConsumeRandomLengthString().c_str();
  offer.info = stream.ConsumeRandomLengthString().c_str();
  offer.uri = stream.ConsumeRandomLengthString().c_str();
  offer.email = stream.ConsumeRandomLengthString().c_str();
  offer.phone = stream.ConsumeRandomLengthString().c_str();
  offer.version = stream.ConsumeIntegral<int32_t>();
  offer.session_id = stream.ConsumeIntegral<int64_t>();
  offer.audio = stream.ConsumeBool();
  offer.video = stream.ConsumeBool();
  offer.data = stream.ConsumeBool();

  // Consume data for the answer
  answer.name = stream.ConsumeRandomLengthString().c_str();
  answer.info = stream.ConsumeRandomLengthString().c_str();
  answer.uri = stream.ConsumeRandomLengthString().c_str();
  answer.email = stream.ConsumeRandomLengthString().c_str();
  answer.phone = stream.ConsumeRandomLengthString().c_str();
  answer.version = stream.ConsumeIntegral<int32_t>();
  answer.session_id = stream.ConsumeIntegral<int64_t>();
  answer.audio = stream.ConsumeBool();
  answer.video = stream.ConsumeBool();
  answer.data = stream.ConsumeBool();

  // Consume data for the offered
  offered.type = stream.ConsumeEnum<janus_sdp_mtype>();
  offered.port = stream.ConsumeIntegral<int32_t>();
  offered.proto = stream.ConsumeRandomLengthString().c_str();
  offered.direction = stream.ConsumeEnum<janus_sdp_mdirection>();

  // Call the function to fuzz
  janus_sdp_generate_answer_mline(&offer, &answer, &offered);

  return 0;
}