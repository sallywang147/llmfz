#include "aom/aom_codec.h"
#include "aom/aomdx.h"
#include "aom_ports/mem_ops.h"
#include "config/aom_config.h"
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#define IVF_FRAME_HDR_SZ (4 + 8) /* 4 byte size + 8 byte timestamp */
#define IVF_FILE_HDR_SZ 32

extern "C" void usage_exit(void) { exit(EXIT_FAILURE); }

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  if (size <= IVF_FILE_HDR_SZ) {
    return 0;
  }

  aom_codec_iface_t *codec_interface = aom_codec_av1_dx();
  aom_codec_ctx_t codec;
  // Set thread count in the range [1, 64].
  const unsigned int threads = (data[IVF_FILE_HDR_SZ] & 0x3f) + 1;
  aom_codec_dec_cfg_t cfg = {threads, 0, 0, !FORCE_HIGHBITDEPTH_DECODING};
  if (aom_codec_dec_init(&codec, codec_interface, &cfg, 0)) {
    return 0;
  }

  data += IVF_FILE_HDR_SZ;
  size -= IVF_FILE_HDR_SZ;

  while (size > IVF_FRAME_HDR_SZ) {
    size_t frame_size = mem_get_le32(data);
    size -= IVF_FRAME_HDR_SZ;
    data += IVF_FRAME_HDR_SZ;
    frame_size = std::min(size, frame_size);

    const aom_codec_err_t err = aom_codec_decode(&codec, data, frame_size, nullptr);
    if (err != AOM_CODEC_OK) {
      return 0;
    }
    aom_codec_iter_t iter = nullptr;
    aom_image_t *img = nullptr;
    while ((img = aom_codec_get_frame(&codec, &iter)) != nullptr) {
      struct yv12_buffer_config *config = aom_img_alloc(img->fmt, img->d_w, img->d_h, 16);
      av1_realloc_and_scale_if_required(&codec.common, img, config, 0, 0, 0, 0, 0, 0);
      aom_img_free(config);
    }
    data += frame_size;
    size -= frame_size;
  }
  aom_codec_destroy(&codec);
  return 0;
}