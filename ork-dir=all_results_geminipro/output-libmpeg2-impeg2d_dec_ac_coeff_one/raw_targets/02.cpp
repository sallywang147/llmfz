#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <vector>

#include "mpeg2d.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  struct _stream_t stream_struct;
  stream_struct.p_buf_start = stream.ConsumeBytes<uint8_t>(stream.ConsumeIntegralInRange<size_t>(0, size)).data();
  stream_struct.buf_size = stream.ConsumeIntegralInRange<size_t>(0, size);
  stream_struct.buf_ptr = stream.ConsumeIntegralInRange<size_t>(0, size);
  stream_struct.buf_end = stream.ConsumeIntegralInRange<size_t>(0, size);
  short sym_len;
  short sym_val;
  impeg2d_dec_ac_coeff_one(&stream_struct, &sym_len, &sym_val);
  return 0;
}