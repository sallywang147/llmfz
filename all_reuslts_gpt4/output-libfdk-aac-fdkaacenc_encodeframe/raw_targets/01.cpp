#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <vector>

#include "aacenc_lib.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  // Initialize the FDK AAC encoder
  HANDLE_AACENCODER hAacEnc;
  if (aacEncOpen(&hAacEnc, 0, 2) != AACENC_OK) {
    return 0;
  }

  // Set the AAC encoder parameters
  if (aacEncoder_SetParam(hAacEnc, AACENC_AOT, 2) != AACENC_OK ||
      aacEncoder_SetParam(hAacEnc, AACENC_SAMPLERATE, 48000) != AACENC_OK ||
      aacEncoder_SetParam(hAacEnc, AACENC_CHANNELMODE, MODE_2) != AACENC_OK ||
      aacEncoder_SetParam(hAacEnc, AACENC_BITRATE, 64000) != AACENC_OK ||
      aacEncoder_SetParam(hAacEnc, AACENC_TRANSMUX, TT_MP4_ADTS) != AACENC_OK ||
      aacEncoder_SetParam(hAacEnc, AACENC_AFTERBURNER, 1) != AACENC_OK) {
    aacEncClose(&hAacEnc);
    return 0;
  }

  // Initialize the AAC encoder
  if (aacEncEncode(hAacEnc, NULL, NULL, NULL, NULL) != AACENC_OK) {
    aacEncClose(&hAacEnc);
    return 0;
  }

  // Initialize the FDK AAC transport encoder
  TRANSPORTENC hTpEnc;
  if (aacEncOpen(&hTpEnc, 0, 2) != AACENC_OK) {
    aacEncClose(&hAacEnc);
    return 0;
  }

  // Set the AAC transport encoder parameters
  if (aacEncoder_SetParam(hTpEnc, AACENC_AOT, 2) != AACENC_OK ||
      aacEncoder_SetParam(hTpEnc, AACENC_SAMPLERATE, 48000) != AACENC_OK ||
      aacEncoder_SetParam(hTpEnc, AACENC_CHANNELMODE, MODE_2) != AACENC_OK ||
      aacEncoder_SetParam(hTpEnc, AACENC_BITRATE, 64000) != AACENC_OK ||
      aacEncoder_SetParam(hTpEnc, AACENC_TRANSMUX, TT_MP4_ADTS) != AACENC_OK ||
      aacEncoder_SetParam(hTpEnc, AACENC_AFTERBURNER, 1) != AACENC_OK) {
    aacEncClose(&hTpEnc);
    aacEncClose(&hAacEnc);
    return 0;
  }

  // Initialize the AAC transport encoder
  if (aacEncEncode(hTpEnc, NULL, NULL, NULL, NULL) != AACENC_OK) {
    aacEncClose(&hTpEnc);
    aacEncClose(&hAacEnc);
    return 0;
  }

  FuzzedDataProvider stream(data, size);

  // We need at least 2 bytes to ensure we have a valid inputBuffer and inputBufferBufSize
  if (stream.remaining_bytes() < 2) {
    aacEncClose(&hTpEnc);
    aacEncClose(&hAacEnc);
    return 0;
  }

  // Consume data for the inputBuffer
  int inputBufferBufSize = stream.ConsumeIntegralInRange<int>(1, stream.remaining_bytes()/2);
  std::vector<short> inputBuffer = stream.ConsumeBytes<short>(inputBufferBufSize);

  // Consume data for the nOutBytes
  int nOutBytes = stream.ConsumeIntegral<int>();

  // Call the target function
  FDKaacEnc_EncodeFrame(&hAacEnc, &hTpEnc, inputBuffer.data(), inputBufferBufSize, &nOutBytes, NULL);

  // Clean up
  aacEncClose(&hTpEnc);
  aacEncClose(&hAacEnc);

  return 0;
}