#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "impeg2d.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  
  // Initialize the _stream_t structure
  struct _stream_t ps_stream;
  ps_stream.u4_ofst = stream.ConsumeIntegral<uint32_t>();
  ps_stream.u4_max_ofst = stream.ConsumeIntegral<uint32_t>();
  ps_stream.u4_bitstream_t = stream.ConsumeIntegral<uint32_t>();
  ps_stream.u4_next_bitstream_t = stream.ConsumeIntegral<uint32_t>();
  ps_stream.u4_bitstream_ofst = stream.ConsumeIntegral<uint32_t>();
  ps_stream.u4_next_bitstream_ofst = stream.ConsumeIntegral<uint32_t>();
  ps_stream.u4_strm_buf_t = stream.ConsumeIntegral<uint32_t>();
  ps_stream.u4_strm_buf_re_load = stream.ConsumeIntegral<uint32_t>();
  ps_stream.u4_strm_buf_size = stream.ConsumeIntegral<uint32_t>();
  ps_stream.u4_strm_buf_max_size = stream.ConsumeIntegral<uint32_t>();
  
  // Initialize the other parameters
  short pu2_sym_len = stream.ConsumeIntegral<short>();
  short pu2_sym_val = stream.ConsumeIntegral<short>();
  
  // Call the function to fuzz
  impeg2d_dec_ac_coeff_one(&ps_stream, &pu2_sym_len, &pu2_sym_val);

  return 0;
}