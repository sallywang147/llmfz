#include <cstdint>
#include <fuzzer/FuzzedDataProvider.h>
#include "encoder.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider stream(data, size);

  // Initialize Encoder
  struct Encoder pEnc;
  pEnc.u8IsIntra = stream.ConsumeIntegral<uint8_t>();
  pEnc.u8QP = stream.ConsumeIntegral<uint8_t>();
  pEnc.u8LastQP = stream.ConsumeIntegral<uint8_t>();
  pEnc.u8Mode = stream.ConsumeIntegral<uint8_t>();
  pEnc.u8MvScale = stream.ConsumeIntegral<uint8_t>();
  pEnc.u8MvRes = stream.ConsumeIntegral<uint8_t>();
  pEnc.u16LostFrames = stream.ConsumeIntegral<uint16_t>();
  pEnc.u16BitstreamSize = stream.ConsumeIntegral<uint16_t>();
  pEnc.u16FrameNum = stream.ConsumeIntegral<uint16_t>();
  pEnc.u16GobNum = stream.ConsumeIntegral<uint16_t>();
  pEnc.u16GobFrameID = stream.ConsumeIntegral<uint16_t>();
  pEnc.u32TimeStamp = stream.ConsumeIntegral<uint32_t>();
  pEnc.u32FrameCount = stream.ConsumeIntegral<uint32_t>();
  pEnc.u32TotalByteCount = stream.ConsumeIntegral<uint32_t>();
  pEnc.u32ByteCount = stream.ConsumeIntegral<uint32_t>();
  pEnc.u32FrmSize = stream.ConsumeIntegral<uint32_t>();
  pEnc.u32BitRate = stream.ConsumeIntegral<uint32_t>();
  pEnc.u32MaxDelay = stream.ConsumeIntegral<uint32_t>();
  pEnc.u32TargetFrameSize = stream.ConsumeIntegral<uint32_t>();
  pEnc.u32Sequence = stream.ConsumeIntegral<uint32_t>();
  pEnc.u32AverageFrameSize = stream.ConsumeIntegral<uint32_t>();

  // Initialize FRAMEINFO
  struct FRAMEINFO frame;
  frame.u8Jitter = stream.ConsumeIntegral<uint8_t>();
  frame.u8FrmState = stream.ConsumeIntegral<uint8_t>();
  frame.u8FrmType = stream.ConsumeIntegral<uint8_t>();
  frame.u8HdrType = stream.ConsumeIntegral<uint8_t>();
  frame.u8Priority = stream.ConsumeIntegral<uint8_t>();
  frame.u8LayerID = stream.ConsumeIntegral<uint8_t>();
  frame.u8Refresh = stream.ConsumeIntegral<uint8_t>();
  frame.u8Reserved = stream.ConsumeIntegral<uint8_t>();
  frame.u16PktCount = stream.ConsumeIntegral<uint16_t>();
  frame.u16LastPktSize = stream.ConsumeIntegral<uint16_t>();
  frame.u32TimeStamp = stream.ConsumeIntegral<uint32_t>();
  frame.u32LastModT = stream.ConsumeIntegral<uint32_t>();
  frame.u32SendT = stream.ConsumeIntegral<uint32_t>();
  frame.u32IP = stream.ConsumeIntegral<uint32_t>();
  frame.u32SeqNum = stream.ConsumeIntegral<uint32_t>();

  // Initialize Bitstream
  struct Bitstream bs;
  bs.u8BitOffset = stream.ConsumeIntegral<uint8_t>();
  bs.u16ByteCount = stream.ConsumeIntegral<uint16_t>();
  bs.u16BufSize = stream.ConsumeIntegral<uint16_t>();
  bs.u32BitCount = stream.ConsumeIntegral<uint32_t>();
  bs.pu8Data = stream.ConsumeBytes<uint8_t>(stream.remaining_bytes()).data();

  // Call the function to fuzz
  FrameCodeB(&pEnc, &frame, &bs);

  return 0;
}