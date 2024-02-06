#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "aom/aom_decoder.h"
#include "aom/aomdx.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  aom_codec_ctx_t codec;
  if (aom_codec_dec_init(&codec, aom_codec_av1_dx(), NULL, 0))
    return 0;

  struct AV1Decoder* pbi = static_cast<struct AV1Decoder*>(codec.decoding_thread_count);

  struct aom_read_bit_buffer rb;
  rb.bit_buffer = stream.ConsumeBytesAsString(stream.ConsumeIntegralInRange(0, size)).c_str();
  rb.bit_buffer_end = rb.bit_buffer + size;
  rb.error_handler = NULL;

  char* data1 = stream.ConsumeBytesAsString(stream.ConsumeIntegralInRange(0, size)).c_str();
  char* data2 = stream.ConsumeBytesAsString(stream.ConsumeIntegralInRange(0, size)).c_str();
  char* data3 = stream.ConsumeBytesAsString(stream.ConsumeIntegralInRange(0, size)).c_str();

  int data4 = stream.ConsumeIntegral<int>();

  read_and_decode_one_tile_list(pbi, &rb, data1, data2, &data3, &data4);

  aom_codec_destroy(&codec);

  return 0;
}