#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <string>

extern "C" {
#include "mpeg2_decoder.h"
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  struct _stream_t ps_stream;
  ps_stream.p_buffer = const_cast<uint8_t*>(data);
  ps_stream.size_buffer = size;
  ps_stream.byte_ptr = 0;
  ps_stream.bit_ptr = 0;

  const bool ai2_code_table = stream.ConsumeBool();
  const bool au2_indexTable = stream.ConsumeBool();
  const short u2_max_len = stream.ConsumeIntegral<short>();

  short res = impeg2d_fast_dec_vld_symbol(&ps_stream, ai2_code_table, au2_indexTable, u2_max_len);

  return 0;
}