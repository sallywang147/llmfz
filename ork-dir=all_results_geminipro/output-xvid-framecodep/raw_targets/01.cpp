#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <vector>

#include "encoder.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  struct Encoder encoder;
  struct Bitstream bitstream;

  encoder.p_Bitstream = &bitstream;
  encoder.p_SPS = nullptr;
  encoder.p_PPS = nullptr;

  FuzzedDataProvider provider(data, size);

  // Initialize the encoder.
  encoder.i_Bitrate = provider.ConsumeIntegralInRange<int>(1, 1000000);
  encoder.i_FrameRate = provider.ConsumeIntegralInRange<int>(1, 100);
  encoder.i_Width = provider.ConsumeIntegralInRange<int>(1, 1920);
  encoder.i_Height = provider.ConsumeIntegralInRange<int>(1, 1080);
  encoder.i_QP = provider.ConsumeIntegralInRange<int>(1, 51);
  encoder.i_RCMode = provider.ConsumeIntegralInRange<int>(0, 2);
  encoder.i_NumberReferenceFrames = provider.ConsumeIntegralInRange<int>(1, 16);
  encoder.i_NumberBFrames = provider.ConsumeIntegralInRange<int>(0, 16);
  encoder.i_IntraPeriod = provider.ConsumeIntegralInRange<int>(1, 100);
  encoder.i_DecodingRefreshType = provider.ConsumeIntegralInRange<int>(0, 3);
  encoder.i_MaxNalUnitLength = provider.ConsumeIntegralInRange<int>(1, 10000);
  encoder.i_HeaderInterval = provider.ConsumeIntegralInRange<int>(1, 1000);
  encoder.i_SliceMode = provider.ConsumeIntegralInRange<int>(0, 6);
  encoder.i_SliceArgument = provider.ConsumeIntegralInRange<int>(1, 1000);
  encoder.i_DisableCabac = provider.ConsumeBool();
  encoder.i_DisableSAO = provider.ConsumeBool();
  encoder.i_DisableDBF = provider.ConsumeBool();
  encoder.i_DisableInterPrediction = provider.ConsumeBool();
  encoder.i_DisableIntraPrediction = provider.ConsumeBool();
  encoder.i_DisableDirectPrediction = provider.ConsumeBool();
  encoder.i_DisableMotionEstimation = provider.ConsumeBool();
  encoder.i_DisableResidualCoding = provider.ConsumeBool();

  // Initialize the bitstream.
  bitstream.p_Buf = nullptr;
  bitstream.i_BufSize = 0;
  bitstream.i_MaxBufSize = 0;

  // Initialize the SPS and PPS.
  encoder.p_SPS = (struct SequenceParameterSet*)calloc(1, sizeof(struct SequenceParameterSet));
  encoder.p_PPS = (struct PictureParameterSet*)calloc(1, sizeof(struct PictureParameterSet));

  // Create the SPS and PPS.
  if (CreateSPS(&encoder) != 0) {
    return 0;
  }
  if (CreatePPS(&encoder) != 0) {
    return 0;
  }

  // Encode a frame.
  FrameCodeP(&encoder, &bitstream);

  // Free the SPS and PPS.
  free(encoder.p_SPS);
  free(encoder.p_PPS);

  // Free the bitstream.
  free(bitstream.p_Buf);

  return 0;
}