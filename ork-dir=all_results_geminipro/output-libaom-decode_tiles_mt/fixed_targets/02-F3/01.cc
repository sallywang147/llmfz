#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstring>
#include <vector>

extern "C" {
#include "aom/aom_decoder.h"
#include "aom/aomdx.h"
#include "aom_ports/mem_ops.h"
#include "config/aom_config.h"
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  if (size <= 0) {
    return 0;
  }
  AV1Decoder *decoder = av1_decoder_create();
  if (!decoder) {
    return 0;
  }
  av1_codec_ctx_t codec_ctx;
  av1_codec_dec_cfg_t cfg = {0};
  av1_codec_dec_init(&codec_ctx, av1_codec_av1_dx(), &cfg, 0);

  FuzzedDataProvider provider(data, size);
  const size_t max_width = 4096;
  const size_t max_height = 2304;
  const int width = provider.ConsumeIntegralInRange<int>(1, max_width);
  const int height = provider.ConsumeIntegralInRange<int>(1, max_height);

  std::vector<uint8_t> buffer(size);
  provider.ConsumeBytes<uint8_t>(buffer.data(), size);
  // Call the decode_tiles_mt function with the correct arguments
  char *output = reinterpret_cast<char *>(
      decode_tiles_mt(&codec_ctx, decoder, reinterpret_cast<char *>(buffer.data()),
                      reinterpret_cast<char *>(buffer.data()) + size, width, height));
  av1_codec_destroy(&codec_ctx);
  av1_decoder_destroy(decoder);
  free(output);
  return 0;
}