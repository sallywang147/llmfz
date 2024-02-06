#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <vector>

#include "mpeg2dec.h"

extern "C" {
#include "mpeg2dec_ac_coeff_zero.h"
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  struct _stream_t stream_struct;
  stream_struct.p_buffer = stream.ConsumeRemainingBytes<uint8_t>().data();
  stream_struct.buffer_size = size;
  stream_struct.next_byte_index = 0;
  stream_struct.bits_left = 8;

  short sym_len;
  short sym_val;
  impeg2d_dec_ac_coeff_zero(&stream_struct, &sym_len, &sym_val);

  return 0;
}
```
The original code has no issues.