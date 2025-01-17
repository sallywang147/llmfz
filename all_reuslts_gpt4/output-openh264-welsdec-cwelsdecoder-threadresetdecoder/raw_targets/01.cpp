#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <vector>

#include "wels/codec_api.h"
#include "wels/codec_def.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  // Initialize the decoder
  WelsDec::ISVCDecoder* decoder = nullptr;
  WelsCreateDecoder(&decoder);
  if (decoder == nullptr) {
    return 0;
  }

  // Initialize the decoder context
  WelsDec::TagWelsDecoderContext* pCtx = nullptr;

  // Initialize the decoder parameters
  SDecodingParam sDecParam;
  memset(&sDecParam, 0, sizeof(sDecParam));
  sDecParam.eOutputColorFormat = stream.ConsumeBool() ? videoFormatI420 : videoFormatRGB;
  sDecParam.uiTargetDqLayer = stream.ConsumeIntegral<uint8_t>();
  sDecParam.eEcActiveIdc = (ERROR_CON_IDC)stream.ConsumeIntegralInRange<int>(0, 2);
  sDecParam.sVideoProperty.eVideoBsType = (VIDEO_BITSTREAM_TYPE)stream.ConsumeIntegralInRange<int>(0, 1);

  // Initialize the decoder
  decoder->Initialize(&sDecParam);

  // Call the function to fuzz
  WelsDec::CWelsDecoder* thisPtr = static_cast<WelsDec::CWelsDecoder*>(decoder);
  thisPtr->ThreadResetDecoder(&pCtx);

  // Clean up
  decoder->Uninitialize();
  WelsDestroyDecoder(decoder);

  return 0;
}