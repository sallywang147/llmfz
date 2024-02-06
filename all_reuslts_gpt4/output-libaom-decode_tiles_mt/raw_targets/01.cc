#include <fuzzer/FuzzedDataProvider.h>
#include <cstddef>
#include <cstdint>
#include <cstdlib>

#include "aom/aom_decoder.h"
#include "aom/aomdx.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  // Initialize the AV1 Decoder
  aom_codec_ctx_t codec;
  if (aom_codec_dec_init(&codec, &aom_codec_av1_dx_algo, NULL, 0)) {
    return 0;
  }

  struct AV1Decoder* pbi = static_cast<AV1Decoder*>(codec.priv);
  if (!pbi) {
    aom_codec_destroy(&codec);
    return 0;
  }

  // Consume data for the parameters of decode_tiles_mt
  int tile_cols = stream.ConsumeIntegral<int>();
  int tile_rows = stream.ConsumeIntegral<int>();
  std::string buf1 = stream.ConsumeBytesAsString(stream.remaining_bytes() / 2);
  std::string buf2 = stream.ConsumeRemainingBytesAsString();

  // Call the target function
  decode_tiles_mt(pbi, const_cast<char*>(buf1.data()), const_cast<char*>(buf2.data()), tile_cols, tile_rows);

  // Clean up
  aom_codec_destroy(&codec);

  return 0;
}