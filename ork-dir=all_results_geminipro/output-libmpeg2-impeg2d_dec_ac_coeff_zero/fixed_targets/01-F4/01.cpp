#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "impeg2d.h"

extern "C" {
#include "libavcodec/avcodec.h"
}

static int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  struct _stream_t stream;
  stream.p_buffer = data;
  stream.i_buffer = size;
  stream.i_cur_byte = 0;
  stream.i_bit_offset = 0;

  short sym_len[256];
  short sym_val[256];

  impeg2d_dec_ac_coeff_zero(&stream, sym_len, sym_val);

  return 0;
}