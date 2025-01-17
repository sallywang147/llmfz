#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "aom/aom_decoder.h"
#include "aom/aomdx.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  aom_codec_ctx_t codec;
  if (aom_codec_dec_init(&codec, aom_codec_av1_dx(), NULL, 0))
    return 0;

  FuzzedDataProvider stream(data, size);

  struct AV1Decoder *pbi = static_cast<AV1Decoder*>(codec.priv);
  struct aom_read_bit_buffer rb;
  rb.bit_buffer = stream.ConsumeRemainingBytes<unsigned char>().data();
  rb.bit_buffer_end = rb.bit_buffer + size;
  rb.error_handler = NULL;

  char *data_end = NULL;
  char *tile_list_payload = NULL;
  char **tile_buffers = NULL;
  int *tile_sizes = NULL;

  int result = read_and_decode_one_tile_list(pbi, &rb, data_end, tile_list_payload, tile_buffers, tile_sizes);

  aom_codec_destroy(&codec);

  return 0;
}