#include <algorithm>
#include <memory>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include "vpx/vp8dx.h"
#include "vpx/vpx_decoder.h"
#include "vpx_ports/mem_ops.h"

#define IVF_FRAME_HDR_SZ (4 + 8) /* 4 byte size + 8 byte timestamp */
#define IVF_FILE_HDR_SZ 32

#define VPXD_INTERFACE(name) VPXD_INTERFACE_(name)
#define VPXD_INTERFACE_(name) vpx_codec_##name##_dx()

extern "C" void usage_exit(void) { exit(EXIT_FAILURE); }

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  if (size <= IVF_FILE_HDR_SZ) {
    return 0;
  }

  vpx_codec_ctx_t codec;
  // Set thread count in the range [1, 64].
  const unsigned int threads = (data[IVF_FILE_HDR_SZ] & 0x3f) + 1;
  vpx_codec_dec_cfg_t cfg = {threads, 0, 0};
  if (vpx_codec_dec_init(&codec, VPXD_INTERFACE(DECODER), &cfg, 0)) {
    return 0;
  }

  if (threads > 1) {
    const int enable = (data[IVF_FILE_HDR_SZ] & 0xa0) != 0;
    const vpx_codec_err_t err = vpx_codec_control(&codec, VP9D_SET_LOOP_FILTER_OPT, enable);
    static_cast<void>(err);
  }

  data += IVF_FILE_HDR_SZ;
  size -= IVF_FILE_HDR_SZ;

  while (size > IVF_FRAME_HDR_SZ) {
    size_t frame_size = mem_get_le32(data);
    size -= IVF_FRAME_HDR_SZ;
    data += IVF_FRAME_HDR_SZ;
    frame_size = std::min(size, frame_size);

    const vpx_codec_err_t err = vpx_codec_decode(&codec, data, frame_size, nullptr, 0);
    static_cast<void>(err);
    vpx_codec_iter_t iter = nullptr;
    vpx_image_t *img = nullptr;
    while ((img = vpx_codec_get_frame(&codec, &iter)) != nullptr) {
      recon_tile_row(nullptr, nullptr, 0, 0, nullptr, 0);
    }
    data += frame_size;
    size -= frame_size;
  }
  vpx_codec_destroy(&codec);
  return 0;
}