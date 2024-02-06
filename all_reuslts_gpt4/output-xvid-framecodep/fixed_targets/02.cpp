#include <cstdint>
#include <fuzzer/FuzzedDataProvider.h>
#include "encoder.h"
#include "bitstream.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider stream(data, size);

  struct Encoder pEnc;
  struct Bitstream bs;

  // Initialize Encoder structure
  pEnc.width = stream.ConsumeIntegral<int>();
  pEnc.height = stream.ConsumeIntegral<int>();
  pEnc.frame_rate = stream.ConsumeIntegral<int>();
  pEnc.frame_increment = stream.ConsumeIntegral<int>();
  pEnc.search_range = stream.ConsumeIntegral<int>();
  pEnc.intra_dc_threshold = stream.ConsumeIntegral<int>();
  pEnc.mv_table_selector = stream.ConsumeIntegral<int>();
  pEnc.qp = stream.ConsumeIntegral<int>();
  pEnc.qp_min = stream.ConsumeIntegral<int>();
  pEnc.qp_max = stream.ConsumeIntegral<int>();
  pEnc.rc_period = stream.ConsumeIntegral<int>();
  pEnc.rc_reaction_period = stream.ConsumeIntegral<int>();
  pEnc.rc_reaction_ratio = stream.ConsumeIntegral<int>();

  // Initialize Bitstream structure
  bs.stream = stream.ConsumeBytesAsString(stream.remaining_bytes()).c_str();
  bs.streamlength = strlen(bs.stream);
  bs.bitpos = stream.ConsumeIntegral<int>();
  bs.bytepos = stream.ConsumeIntegral<int>();
  bs.bitstream_length = stream.ConsumeIntegral<int>();
  bs.eob = stream.ConsumeBool();

  // Call the target function
  FrameCodeP(&pEnc, &bs);

  return 0;
}