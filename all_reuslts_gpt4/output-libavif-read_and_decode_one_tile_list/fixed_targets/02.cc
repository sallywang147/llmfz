#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "aom/aom_decoder.h"
#include "aom/aomdx.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  if (size < 1) {
    return 0;
  }

  aom_codec_ctx_t codec;
  if(aom_codec_dec_init(&codec, &aom_codec_av1_dx_algo, NULL, 0)) {
    return 0;
  }

  FuzzedDataProvider stream(data, size);

  struct AV1Decoder *pbi = static_cast<AV1Decoder*>(codec.priv);
  struct aom_read_bit_buffer rb;
  aom_read_bit_buffer_init(&rb, data, size);

  std::string str1 = stream.ConsumeRandomLengthString();
  char* ptr1 = str1.c_str();

  std::string str2 = stream.ConsumeRandomLengthString();
  char* ptr2 = str2.c_str();

  std::string str3 = stream.ConsumeRandomLengthString();
  char* ptr3 = str3.c_str();

  int int_arg = stream.ConsumeIntegral<int>();

  read_and_decode_one_tile_list(pbi, &rb, ptr1, ptr2, &ptr3, &int_arg);

  aom_codec_destroy(&codec);

  return 0;
}