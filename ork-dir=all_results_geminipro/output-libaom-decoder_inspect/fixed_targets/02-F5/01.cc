#include "aom/aom_decoder.h"
#include "aom/aomdx.h"
#include "aom_ports/mem_ops.h"
#include "config/aom_config.h"
#include <algorithm>
#include <memory>
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
  aom_codec_alg_priv_t *codec_priv = nullptr;
  if (aom_codec_dec_init(&codec_priv, codec_interface, nullptr, 0)) {
    return 0;
  }

  data += IVF_FILE_HDR_SZ;
  size -= IVF_FILE_HDR_SZ;

  while (size > IVF_FRAME_HDR_SZ) {
    size_t frame_size = mem_get_le32(data);
    size -= IVF_FRAME_HDR_SZ;
    data += IVF_FRAME_HDR_SZ;
    frame_size = std::min(size, frame_size);

    const aom_codec_err_t err = aom_codec_decode(codec_priv, (const uint8_t *)data, frame_size, nullptr, 0);
    static_cast<void>(err);

    data += frame_size;
    size -= frame_size;
  }

  // Call decoder_inspect function here.
  aom_codec_inspect(codec_priv, nullptr, 0, nullptr);

  aom_codec_destroy(codec_priv);
  return 0;
}