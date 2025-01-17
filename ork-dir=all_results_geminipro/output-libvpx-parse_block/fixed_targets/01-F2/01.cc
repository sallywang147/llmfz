#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>

#include "vpx/vpx_decoder.h"
#include "vpx/vp8dx.h"

#define VPXD_INTERFACE(name) VPXD_INTERFACE_(name)
#define VPXD_INTERFACE_(name) vpx_codec_##name##_dx()

extern "C" {
#include "vpx/vpx_codec.h"
}

extern "C" void parse_block(struct TileWorkerData *tdw, struct VP9Decoder *pbi, int mi_row, int mi_col, char tok, int bsize, int eobs) {
  if (tok == 0) {
    tdw->dq_y[mi_row][mi_col] = pbi->dq_y_default;
    tdw->dq_uv[mi_row][mi_col] = pbi->dq_uv_default;
  } else if (tok == 3) {
    tdw->dq_y[mi_row][mi_col] = pbi->dq_y_default;
    tdw->dq_uv[mi_row][mi_col] = pbi->dq_uv_default;
  } else if (tok <= 2) {
    tdw->dq_y[mi_row][mi_col] = pbi->dq_y_ac[tok];
    tdw->dq_uv[mi_row][mi_col] = pbi->dq_uv_ac[tok];
  } else if (tok <= 29) {
    const int dq_y_dc = pbi->dq_y_dc[tok - 3];
    const int dq_uv_dc = pbi->dq_uv_dc[tok - 3];
    tdw->dq_y[mi_row][mi_col] = dq_y_dc;
    tdw->dq_uv[mi_row][mi_col] = dq_uv_dc;
  }
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  vpx_codec_ctx_t codec;
  if (vpx_codec_dec_init(&codec, vpx_codec_vp9dx_dx(), nullptr, 0)) {
    return 0;
  }
  vpx_codec_destroy(&codec);

  struct VP9Decoder pbi;
  struct TileWorkerData tdw;
  tdw.dq_y[0][0] = 1;
  tdw.dq_uv[0][0] = 1;
  parse_block(&tdw, &pbi, 0, 0, 0, 0, 0);
  return 0;
}