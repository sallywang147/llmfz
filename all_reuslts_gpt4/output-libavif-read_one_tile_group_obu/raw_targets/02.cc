#include <fuzzer/FuzzedDataProvider.h>
#include <aom/aom_decoder.h>
#include <aom/aomdx.h>
#include <stddef.h>
#include <stdint.h>
#include <string.h>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  aom_codec_ctx_t codec;
  if (aom_codec_dec_init(&codec, aom_codec_av1_dx(), NULL, 0))
    return 0;

  struct AV1Decoder* pbi = static_cast<struct AV1Decoder*>(codec.dec);
  FuzzedDataProvider stream(data, size);

  // Prepare parameters for read_one_tile_group_obu
  struct aom_read_bit_buffer rb;
  int tile_group_start = stream.ConsumeIntegral<int>();
  char* data_end = const_cast<char*>(reinterpret_cast<const char*>(data + size));
  char* p_data_end = data_end;
  char* saved_buf = const_cast<char*>(reinterpret_cast<const char*>(data));
  char** p_data = &saved_buf;
  int* p_data_end_pos = &tile_group_start;
  int is_last_tile_group = stream.ConsumeBool();

  // Call the target function
  read_one_tile_group_obu(pbi, &rb, tile_group_start, data_end, p_data_end, p_data, p_data_end_pos, is_last_tile_group);

  aom_codec_destroy(&codec);
  return 0;
}