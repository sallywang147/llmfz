#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <cstring>

#include "mpeg2dec.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  struct _stream_t s = {};
  s.p_buffer = stream.ConsumeRemainingBytes<uint8_t>().data();
  s.size = size;

  short sym_len = 0;
  short sym_val = 0;
  impeg2d_dec_ac_coeff_zero(&s, &sym_len, &sym_val);

  return 0;
}