#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <cstring>
#include <vector>

#include "aacenc_lib.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  const int sample_rate = stream.ConsumeIntegralInRange<int>(0, 192000);
  const int channel_count = stream.ConsumeIntegralInRange<int>(1, 8);
  const int bitrate = stream.ConsumeIntegralInRange<int>(16000, 1000000);
  const int latency = stream.ConsumeIntegralInRange<int>(0, 1000);
  const int profile = stream.ConsumeIntegralInRange<int>(1, 5);
  const int format = stream.ConsumeIntegralInRange<int>(0, 3);
  const int channels = stream.ConsumeIntegralInRange<int>(0, 3);
  const int bitrate_mode = stream.ConsumeIntegralInRange<int>(0, 1);
  const int vbr_quality = stream.ConsumeIntegralInRange<int>(0, 9);
  const int bitrate_target = stream.ConsumeIntegralInRange<int>(0, 1000000);
  const int bitrate_min = stream.ConsumeIntegralInRange<int>(0, 1000000);
  const int bitrate_max = stream.ConsumeIntegralInRange<int>(0, 1000000);
  const int frame_length = stream.ConsumeIntegralInRange<int>(0, 10000);
  const int channels_out = stream.ConsumeIntegralInRange<int>(0, 3);
  const int crc = stream.ConsumeBool();

  AACENC_InfoStruct info = {0};
  AACENC_ERROR err = aacEncOpen(&info.enchandler, 0, sample_rate);
  if (err != AACENC_OK) {
    return 0;
  }

  err = aacEncoder_SetParam(info.enchandler, AACENC_AOT, AOT_AAC_LC);
  if (err != AACENC_OK) {
    aacEncClose(&info.enchandler);
    return 0;
  }

  err = aacEncoder_SetParam(info.enchandler, AACENC_SAMPLERATE, sample_rate);
  if (err != AACENC_OK) {
    aacEncClose(&info.enchandler);
    return 0;
  }

  err = aacEncoder_SetParam(info.enchandler, AACENC_CHANNELMODE, channel_count);
  if (err != AACENC_OK) {
    aacEncClose(&info.enchandler);
    return 0;
  }

  err = aacEncoder_SetParam(info.enchandler, AACENC_CHANNELORDER, channels);
  if (err != AACENC_OK) {
    aacEncClose(&info.enchandler);
    return 0;
  }

  err = aacEncoder_SetParam(info.enchandler, AACENC_BITRATE, bitrate);
  if (err != AACENC_OK) {
    aacEncClose(&info.enchandler);
    return 0;
  }

  err = aacEncoder_SetParam(info.enchandler, AACENC_LTP_PREDICT, 1);
  if (err != AACENC_OK) {
    aacEncClose(&info.enchandler);
    return 0;
  }

  err = aacEncoder_SetParam(info.enchandler, AACENC_SBR_MODE, 1);
  if (err != AACENC_OK) {
    aacEncClose(&info.enchandler);
    return 0;
  }

  err = aacEncoder_SetParam(info.enchandler, AACENC_PREDICTION_METHOD, 1);
  if (err != AACENC_OK) {
    aacEncClose(&info.enchandler);
    return 0;
  }

  err = aacEncoder_SetParam(info.enchandler, AACENC_TRANSIENT_ATTACK, 1);
  if (err != AACENC_OK) {
    aacEncClose(&info.enchandler);
    return 0;
  }

  err = aacEncoder_SetParam(info.enchandler, AACENC_AFTERBURNER, 1);
  if (err != AACENC_OK) {
    aacEncClose(&info.enchandler);
    return 0;
  }

  AACENC_BufDesc in_buf_desc = {0};
  AACENC_BufDesc out_buf_desc = {0};
  AACENC_InArgs in_args = {0};
  QMF_SCALE_FACTOR out_args = {0};

  const size_t in_buf_size = stream.ConsumeIntegralInRange<size_t>(0, 1024);
  const size_t out_buf_size = stream.ConsumeIntegralInRange<size_t>(0, 1024);
  std::vector<uint8_t> in_buf(in_buf_size);
  std::vector<uint8_t> out_buf(out_buf_size);
  stream.Read(in_buf.data(), in_buf.size());

  in_buf_desc.numBufs = 1;
  in_buf_desc.bufs = &in_buf[0];
  in_buf_desc.bufferIdentifiers = nullptr;
  in_buf_desc.bufSizes = &in_buf_size;

  out_buf_desc.numBufs = 1;
  out_buf_desc.bufs = &out_buf[0];
  out_buf_desc.bufferIdentifiers = nullptr;
  out_buf_desc.bufSizes = &out_buf_size;

  in_args.numInSamples = in_buf_size;
  in_args.numValidSamples = in_buf_size;
  in_args.lastPartOfInput = 1;

  err = aacEncEncode(info.enchandler, &in_buf_desc, &out_buf_desc, &in_args,
                     &out_args);
  if (err != AACENC_OK) {
    aacEncClose(&info.enchandler);
    return 0;
  }

  aacEncClose(&info.enchandler);
  return 0;
}