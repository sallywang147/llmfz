#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <cstring>

#include "mpeg2dec.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  struct _stream_t stream_struct;
  memset(&stream_struct, 0, sizeof(stream_struct));

  stream_struct.p_next_byte = stream.ConsumeBytes<uint8_t>(size).data();
  stream_struct.size_remaining = size;

  short sym_len, sym_val;
  impeg2d_dec_ac_coeff_one(&stream_struct, &sym_len, &sym_val);
  return 0;
}

int impeg2d_dec_ac_coeff_one(struct _stream_t* stream, short* sym_len, short* sym_val);