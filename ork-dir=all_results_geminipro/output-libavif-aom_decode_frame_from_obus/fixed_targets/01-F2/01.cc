#include <aom/aom_decoder.h>
#include <aom/aomdx.h>
#include <fuzzer/FuzzedDataProvider.h>
#include <stdlib.h>

extern "C" {
#include <aom/aom_integer.h>
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider fdp(data, size);

  aom_codec_ctx_t codec_ctx;
  aom_codec_dec_cfg_t dec_cfg;
  aom_codec_err_t res = aom_codec_dec_init(&codec_ctx, aom_codec_av1_dx(), &dec_cfg, 0);
  if (res != AOM_CODEC_OK) {
    return 0;
  }

  AV1Decoder *dec = reinterpret_cast<AV1Decoder *>(codec_ctx.priv);

  char *obus_start = nullptr;
  char *obus_end = nullptr;
  char *frame_start = nullptr;
  int ret = aom_decode_frame_from_obus(dec, obus_start, obus_end, &frame_start);
  if (ret != AOM_CODEC_OK) {
    aom_codec_dec_destroy(&codec_ctx);
    return 0;
  }

  aom_codec_dec_destroy(&codec_ctx);
  return 0;
}