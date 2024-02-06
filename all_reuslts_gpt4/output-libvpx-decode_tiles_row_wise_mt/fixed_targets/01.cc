#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include "fuzzer/FuzzedDataProvider.h"
#include "vp9/decoder/vp9_decoder.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider stream(data, size);

  struct VP9Decoder *pbi = vp9_decoder_create();
  if (pbi == NULL) {
    return 0;
  }

  size_t data1_size = stream.remaining_bytes() / 2;
  size_t data2_size = stream.remaining_bytes() - data1_size;

  std::string data1 = stream.ConsumeBytesAsString(data1_size);
  std::string data2 = stream.ConsumeBytesAsString(data2_size);

  decode_tiles_row_wise_mt(pbi, const_cast<char*>(data1.c_str()), const_cast<char*>(data2.c_str()));

  vp9_decoder_remove(pbi);

  return 0;
}