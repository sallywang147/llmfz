#include <cstdint>
#include <fuzzer/FuzzedDataProvider.h>
#include "encoder.h"
#include "bitstream.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider stream(data, size);

  // Initialize Encoder and Bitstream structures
  struct Encoder pEnc;
  struct Bitstream bs;

  // Consume data for Encoder structure
  pEnc.width = stream.ConsumeIntegral<int>();
  pEnc.height = stream.ConsumeIntegral<int>();
  pEnc.bitrate = stream.ConsumeIntegral<int>();
  pEnc.framerate = stream.ConsumeIntegral<int>();
  pEnc.I_vop_interval = stream.ConsumeIntegral<int>();
  pEnc.no_of_pframes = stream.ConsumeIntegral<int>();
  pEnc.quant = stream.ConsumeIntegral<int>();
  pEnc.motion = stream.ConsumeIntegral<int>();
  pEnc.rdopt = stream.ConsumeIntegral<int>();
  pEnc.format = stream.ConsumeIntegral<int>();

  // Consume data for Bitstream structure
  bs.streamBuffer = stream.ConsumeBytes<uint8_t>(stream.remaining_bytes()).data();
  bs.bitstream_length = stream.ConsumeIntegral<int>();
  bs.byte_pos = stream.ConsumeIntegral<int>();
  bs.bit_pos = stream.ConsumeIntegral<int>();
  bs.streamBuffer_size = stream.ConsumeIntegral<int>();

  // Call the target function
  FrameCodeP(&pEnc, &bs);

  return 0;
}