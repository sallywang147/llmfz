#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <vector>

#include "fdk-aac/aacenc_lib.h"
#include "fdk-aac/transport.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  const uint8_t channels = stream.ConsumeIntegral<uint8_t>();
  const uint8_t bitrate = stream.ConsumeIntegral<uint8_t>();
  const uint8_t sample_rate = stream.ConsumeIntegral<uint8_t>();
  const uint8_t profile = stream.ConsumeIntegral<uint8_t>();
  const uint8_t channel_mode = stream.ConsumeIntegral<uint8_t>();
  const uint8_t frame_length = stream.ConsumeIntegral<uint8_t>();

  AACENC_InfoStruct info = {0};
  AACENC_ERROR err = aacEncOpen(&info.enchandler, 0, channels);
  if (err != AACENC_OK) {
    return 0;
  }

  err = aacEncoder_SetParam(info.enchandler, AACENC_AOT, AOT_AAC_LC);
  if (err != AACENC_OK) {
    aacEncClose(&info.enchandler);
    return 0;
  }

  err = aacEncoder_SetParam(info.enchandler, AACENC_BITRATE, bitrate);
  if (err != AACENC_OK) {
    aacEncClose(&info.enchandler);
    return 0;
  }

  err = aacEncoder_SetParam(info.enchandler, AACENC_SAMPLERATE, sample_rate);
  if (err != AACENC_OK) {
    aacEncClose(&info.enchandler);
    return 0;
  }

  err = aacEncoder_SetParam(info.enchandler, AACENC_CHANNELMODE, channel_mode);
  if (err != AACENC_OK) {
    aacEncClose(&info.enchandler);
    return 0;
  }

  err = aacEncoder_SetParam(info.enchandler, AACENC_AACPROFILE, profile);
  if (err != AACENC_OK) {
    aacEncClose(&info.enchandler);
    return 0;
  }

  err = aacEncoder_SetParam(info.enchandler, AACENC_FRAME_LENGTH, frame_length);
  if (err != AACENC_OK) {
    aacEncClose(&info.enchandler);
    return 0;
  }

  AACENC_BufDesc in_buf = {0};
  AACENC_BufDesc out_buf = {0};
  int in_identifier = IN_AUDIO_DATA;
  int in_size, in_elem_size;
  int out_identifier = OUT_BITSTREAM_DATA;
  int out_size, out_elem_size;

  const size_t input_buffer_size = stream.ConsumeIntegralInRange<size_t>(
      1, std::numeric_limits<size_t>::max());
  std::vector<int16_t> input_buffer(input_buffer_size);
  for (size_t i = 0; i < input_buffer_size; ++i) {
    input_buffer[i] = stream.ConsumeIntegral<int16_t>();
  }

  in_buf.numBufs = 1;
  in_buf.bufs = &input_buffer[0];
  in_buf.bufSizes = &input_buffer_size;
  in_buf.bufferIdentifiers = &in_identifier;

  out_buf.numBufs = 1;
  out_buf.bufs = nullptr;
  out_buf.bufSizes = &out_size;
  out_buf.bufferIdentifiers = &out_identifier;

  err = aacEncEncode(info.enchandler, &in_buf, &out_buf);
  if (err != AACENC_OK) {
    aacEncClose(&info.enchandler);
    return 0;
  }

  aacEncClose(&info.enchandler);
  return 0;
}