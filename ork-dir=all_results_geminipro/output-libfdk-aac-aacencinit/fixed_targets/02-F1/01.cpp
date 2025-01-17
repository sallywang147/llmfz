#include "aacenc_lib.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  struct AACENCODER *hAacEncoder = NULL;
  struct USER_PARAM config;
  memset(&config, 0, sizeof(config));

  FuzzedDataProvider stream(data, size);
  config.codecType = stream.ConsumeIntegral<int>();
  config.bitRate = stream.ConsumeIntegral<int>();
  config.nChannels = stream.ConsumeIntegral<int>();
  config.sampleRate = stream.ConsumeIntegral<int>();
  config.frameLength = stream.ConsumeIntegral<int>();
  config.aacParams.profile = stream.ConsumeIntegral<int>();
  config.aacParams.chanMode = stream.ConsumeIntegral<int>();
  config.aacParams.quantFrm = stream.ConsumeIntegral<int>();
  config.aacParams.bitRateMode = stream.ConsumeIntegral<int>();
  config.aacParams.audioObjectType = stream.ConsumeIntegral<int>();
  config.aacParams.sbrEnabled = stream.ConsumeIntegral<int>();
  config.aacParams.psEnable = stream.ConsumeIntegral<int>();
  config.aacParams.sbrMode = stream.ConsumeIntegral<int>();
  config.aacParams.sbrRate = stream.ConsumeIntegral<int>();
  config.aacParams.sbrDelay = stream.ConsumeIntegral<int>();
  config.aacParams.msMaskPresent = stream.ConsumeIntegral<int>();
  config.aacParams.msPresent = stream.ConsumeIntegral<int>();
  config.aacParams.ErAacLsb = stream.ConsumeIntegral<int>();
  config.aacParams.ErAacBitRate = stream.ConsumeIntegral<int>();
  config.aacParams.ErAacFrameLength = stream.ConsumeIntegral<int>();
  config.aacParams.ErAacToolPresent = stream.ConsumeIntegral<int>();
  config.aacParams.aacSectionDataResilienceFlag = stream.ConsumeIntegral<int>();
  config.aacParams.aacScalefactorResilienceFlag = stream.ConsumeIntegral<int>();
  config.aacParams.aacLfeFlag = stream.ConsumeIntegral<int>();
  config.aacParams.extensionFlag = stream.ConsumeIntegral<int>();
  config.aacParams.directMapping = stream.ConsumeIntegral<int>();
  config.aacParams.warpedInfoPresentFlag = stream.ConsumeIntegral<int>();
  config.aacParams.fillElementFlag = stream.ConsumeIntegral<int>();
  config.aacParams.isDependentCoding = stream.ConsumeIntegral<int>();
  config.aacParams.highBandPresentFlag = stream.ConsumeIntegral<int>();
  config.aacParams.psPresentFlag = stream.ConsumeIntegral<int>();
  config.aacParams.escapeValue = stream.ConsumeIntegral<int>();

  int init_flags = stream.ConsumeIntegral<int>();
  int ret = aacEncInit(&hAacEncoder, init_flags, &config);
  if (ret != AACENC_OK) {
    return 0;
  }
  uint8_t *input_buffer = (uint8_t *)malloc(config.frameLength * 2);
  uint8_t *output_buffer = (uint8_t *)malloc(config.frameLength * 2);
  AACENC_BufDesc in_buf = {0}, out_buf = {0};
  in_buf.numBufs = 1;
  in_buf.bufs = &input_buffer;
  in_buf.bufferIdentifiers = NULL;
  in_buf.bufSizes = &config.frameLength * 2;
  out_buf.numBufs = 1;
  out_buf.bufs = &output_buffer;
  out_buf.bufferIdentifiers = NULL;
  out_buf.bufSizes = &config.frameLength * 2;
  aacEncEncode(hAacEncoder, &in_buf, &out_buf, NULL, NULL);
  aacEncClose(hAacEncoder);
  free(input_buffer);
  free(output_buffer);
  return 0;
}