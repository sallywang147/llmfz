#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "aom/aom_decoder.h"
#include "aom/aomdx.h"

extern "C" {
#include "aom/aom_dec.h"
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  aom_codec_ctx_t codec;
  aom_codec_dec_cfg_t cfg = aom_codec_dec_cfg_t();
  cfg.threads = 1;
  if (aom_codec_dec_init(&codec, aom_codec_av1_dx(), &cfg, 0)) {
    return 0;
  }
  aom_codec_stream_info_t si;
  aom_codec_peek_stream_info(&codec, &si);
  aom_read_bit_buffer rb = aom_read_bit_buffer();
  aom_codec_control(&codec, AOMD_SET_BIT_BUFFER, &rb);
  aom_codec_control(&codec, AOMD_SET_DECODE_TILE_ROW, &si.tile_rows);
  aom_codec_control(&codec, AOMD_SET_DECODE_TILE_COL, &si.tile_cols);
  aom_codec_control(&codec, AOMD_SET_USE_HIGHBITDEPTH, &si.bit_depth);
  aom_codec_control(&codec, AOMD_SET_DECODE_MODE, &si.mode);
  aom_codec_control(&codec, AOMD_SET_ALLOW_HIGHBITDEPTH, &si.bit_depth);
  aom_codec_control(&codec, AOMD_SET_ALLOW_LOWBITDEPTH, &si.bit_depth);
  aom_codec_control(&codec, AOMD_SET_CPU_USED, &si.cpu_used);
  aom_codec_control(&codec, AOMD_SET_ERROR_RESILIENT_MODE, &si.error_resilient_mode);
  aom_codec_control(&codec, AOMD_SET_FRAME_PARALLEL_DECODING, &si.frame_parallel_decoding_mode);
  aom_codec_control(&codec, AOMD_SET_TILE_PARALLEL_DECODING, &si.tile_parallel_decoding_mode);
  aom_codec_control(&codec, AOMD_SET_UNAUTHORIZED_HEADER_CHECKING, &si.unauthorised_header_detection);
  aom_codec_control(&codec, AOMD_SET_BORDER_IN_PIXELS, &si.border);
  aom_codec_control(&codec, AOMD_SET_MAX_WIDTH, &si.frame_width);
  aom_codec_control(&codec, AOMD_SET_MAX_HEIGHT, &si.frame_height);
  aom_codec_control(&codec, AOMD_SET_MAX_INTER_FRAME_FWD_REFS, &si.max_inter_frame_fwd_refs);
  aom_codec_control(&codec, AOMD_SET_ENABLE_RESYNCHRONIZATION, &si.enable_resync);
  aom_codec_control(&codec, AOMD_SET_DECODE_HEADER, &si.header_size);
  aom_codec_control(&codec, AOMD_SET_BITSTREAM_PROFILE, &si.profile);
  aom_codec_control(&codec, AOMD_SET_TEMPORAL_LAYER_ID, &si.temporal_layer_id);
  aom_codec_control(&codec, AOMD_SET_SPATIAL_LAYER_ID, &si.spatial_layer_id);
  aom_codec_control(&codec, AOMD_SET_ROBUST_STREAMING, &si.robust_streaming);
  aom_codec_control(&codec, AOMD_SET_STRIP_MASKING, &si.strip_mask);
  aom_codec_control(&codec, AOMD_SET_HIGH_PRECISION_MV, &si.high_precision_mv);
  aom_codec_control(&codec, AOMD_SET_FRAME_PERIODICITY, &si.frame_periodicity);
  aom_codec_control(&codec, AOMD_SET_NUM_OF_REF_FRAMES, &si.num_ref_frames);
  aom_codec_control(&codec, AOMD_SET_REF_FRAME_FLAGS, &si.ref_frame_flags);
  aom_codec_control(&codec, AOMD_SET_FRAME_SIZE_DECODED, &si.frame_size_decoded);
  aom_codec_control(&codec, AOMD_SET_FRAME_SIZE_UPSAMPLED, &si.frame_size_upsampled);
  aom_codec_control(&codec, AOMD_SET_DISPLAY_SIZE, &si.display_size);
  aom_codec_control(&codec, AOMD_SET_BIT_DEPTH, &si.bit_depth);
  aom_codec_control(&codec, AOMD_SET_COLOR_SPACE, &si.color_space);
  aom_codec_control(&codec, AOMD_SET_CHROMA_SAMPLE_POSITION, &si.chroma_sample_position);
  aom_codec_control(&codec, AOMD_SET_TRANSFER_FUNCTIONS, &si.transfer_function);
  aom_codec_control(&codec, AOMD_SET_COLOR_RANGE, &si.color_range);

  FuzzedDataProvider fdp(data, size);
  std::vector<uint8_t> obu_buffer(fdp.ConsumeRemainingBytes<uint8_t>());

  // Fix: Include the necessary header for AV1Decoder.
  #include "aom/aom_av1_decoder.h"

  AV1Decoder *decoder = new AV1Decoder();

  decoder->aom_dec_ctx_ = &codec;
  decoder->obu_buffer_ = &obu_buffer;
  decoder->obu_size_ = obu_buffer.size();

  decoder->read_one_tile_group_obu();

  delete decoder;
  aom_codec_dec_destroy(&codec);
  return 0;
}