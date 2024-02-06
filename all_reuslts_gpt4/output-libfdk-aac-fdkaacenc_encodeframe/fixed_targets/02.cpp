#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <vector>

#include "aacenc_lib.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  if (size < 2) {
    return 0;
  }

  FuzzedDataProvider stream(data, size);

  // Initialize the AAC encoder
  AACENC_ERROR error;
  HANDLE_AACENCODER handle;
  if ((error = aacEncOpen(&handle, 0, 2)) != AACENC_OK) {
    return 0;
  }

  // Set the AAC encoder configuration
  if (aacEncoder_SetParam(handle, AACENC_AOT, 2) != AACENC_OK ||
      aacEncoder_SetParam(handle, AACENC_SAMPLERATE, 48000) != AACENC_OK ||
      aacEncoder_SetParam(handle, AACENC_CHANNELMODE, MODE_2) != AACENC_OK ||
      aacEncoder_SetParam(handle, AACENC_BITRATE, 64000) != AACENC_OK ||
      aacEncoder_SetParam(handle, AACENC_TRANSMUX, 0) != AACENC_OK ||
      aacEncoder_SetParam(handle, AACENC_AFTERBURNER, 1) != AACENC_OK) {
    aacEncClose(&handle);
    return 0;
  }

  if ((error = aacEncEncode(handle, NULL, NULL, NULL, NULL)) != AACENC_OK) {
    aacEncClose(&handle);
    return 0;
  }

  AACENC_InfoStruct info = { 0 };
  if ((error = aacEncInfo(handle, &info)) != AACENC_OK) {
    aacEncClose(&handle);
    return 0;
  }

  // Prepare the input buffer
  std::vector<short> inputBuffer(stream.ConsumeIntegralInRange<size_t>(0, size / 2));
  stream.ConsumeData(inputBuffer.data(), inputBuffer.size() * sizeof(short));

  // Prepare the output buffer
  std::vector<uint8_t> outputBuffer(info.maxOutBufBytes);
  int nOutBytes = 0;

  // Call the function to fuzz
  FDKaacEnc_EncodeFrame(handle, NULL, inputBuffer.data(), inputBuffer.size(), &nOutBytes, NULL);

  // Clean up
  aacEncClose(&handle);

  return 0;
}