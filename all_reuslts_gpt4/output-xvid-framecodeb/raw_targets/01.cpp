#include <cstdint>
#include <fuzzer/FuzzedDataProvider.h>
#include "encoder.h"
#include "bitstream.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider stream(data, size);

  // Initialize the Encoder object
  struct Encoder pEnc;
  memset(&pEnc, 0, sizeof(pEnc));

  // Initialize the FRAMEINFO object
  struct FRAMEINFO frame;
  memset(&frame, 0, sizeof(frame));

  // Initialize the Bitstream object
  struct Bitstream bs;
  memset(&bs, 0, sizeof(bs));

  // Consume data for the Bitstream
  size_t bitstream_size = stream.ConsumeIntegralInRange<size_t>(0, size);
  std::vector<uint8_t> bitstream_data = stream.ConsumeBytes<uint8_t>(bitstream_size);
  bs.streamBuffer = bitstream_data.data();
  bs.streamBufferSize = bitstream_size;

  // Call the target function
  FrameCodeB(&pEnc, &frame, &bs);

  return 0;
}