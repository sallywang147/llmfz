#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "impeg2d.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  
  struct _stream_t ps_stream;
  short pu2_sym_len;
  short pu2_sym_val;

  // Initialize the struct
  ps_stream.u4_ofst = stream.ConsumeIntegral<uint32_t>();
  ps_stream.u4_max_ofst = stream.ConsumeIntegral<uint32_t>();
  ps_stream.u4_bit_ofst = stream.ConsumeIntegral<uint32_t>();
  ps_stream.u4_max_bit_ofst = stream.ConsumeIntegral<uint32_t>();
  ps_stream.u4_cur_word = stream.ConsumeIntegral<uint32_t>();
  ps_stream.u4_nxt_word = stream.ConsumeIntegral<uint32_t>();
  ps_stream.u4_prev_word = stream.ConsumeIntegral<uint32_t>();
  ps_stream.u4_init_done = stream.ConsumeIntegral<uint32_t>();
  ps_stream.u4_strm_buf = stream.ConsumeIntegral<uint32_t>();
  ps_stream.u4_strm_ofst = stream.ConsumeIntegral<uint32_t>();
  ps_stream.u4_strm_buf_len = stream.ConsumeIntegral<uint32_t>();
  ps_stream.u4_num_bit_shifts = stream.ConsumeIntegral<uint32_t>();
  ps_stream.u4_num_bits_reqd = stream.ConsumeIntegral<uint32_t>();
  ps_stream.u4_num_ones = stream.ConsumeIntegral<uint32_t>();
  ps_stream.u4_num_zeros = stream.ConsumeIntegral<uint32_t>();
  ps_stream.u4_num_bits_in_wrd = stream.ConsumeIntegral<uint32_t>();
  ps_stream.u4_num_zeros_32 = stream.ConsumeIntegral<uint32_t>();
  ps_stream.u4_num_zeros_8 = stream.ConsumeIntegral<uint32_t>();
  ps_stream.u4_num_zeros_16 = stream.ConsumeIntegral<uint32_t>();
  ps_stream.u4_num_zeros_24 = stream.ConsumeIntegral<uint32_t>();
  ps_stream.u4_num_zeros_4 = stream.ConsumeIntegral<uint32_t>();
  ps_stream.u4_num_zeros_12 = stream.ConsumeIntegral<uint32_t>();
  ps_stream.u4_num_zeros_20 = stream.ConsumeIntegral<uint32_t>();
  ps_stream.u4_num_zeros_28 = stream.ConsumeIntegral<uint32_t>();

  // Call the function under test
  impeg2d_dec_ac_coeff_zero(&ps_stream, &pu2_sym_len, &pu2_sym_val);

  return 0;
}