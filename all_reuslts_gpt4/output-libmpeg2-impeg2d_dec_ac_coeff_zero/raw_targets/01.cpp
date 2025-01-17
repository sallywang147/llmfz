#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "impeg2d.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider fuzzed_data(data, size);

  // Define and initialize the parameters
  struct _stream_t ps_stream;
  short pu2_sym_len = 0;
  short pu2_sym_val = 0;

  // Fill the stream structure
  if (fuzzed_data.remaining_bytes() > 0) {
    size_t stream_size = fuzzed_data.ConsumeIntegralInRange<size_t>(1, fuzzed_data.remaining_bytes());
    std::vector<uint8_t> stream_data = fuzzed_data.ConsumeBytes<uint8_t>(stream_size);
    ps_stream.u4_ofst = 0;
    ps_stream.u4_bits_left = stream_size * 8;  // bits
    ps_stream.pu1_buf = stream_data.data();
    ps_stream.u4_max_ofst = stream_size;
    ps_stream.u4_next_word = 0;
    ps_stream.u4_next_word_msb = 0;
    ps_stream.u4_bit_ofst = 0;
    ps_stream.u4_cur_word = 0;
    ps_stream.u4_cur_word_msb = 0;
    ps_stream.u4_prev_bit_ofst = 0;
    ps_stream.u4_prev_max_ofst = 0;
    ps_stream.u4_num_zeros = 0;
    ps_stream.u4_stuff_zeros = 0;
    ps_stream.u4_num_stuff_zeros = 0;
    ps_stream.u4_num_emu_zeros = 0;
    ps_stream.u4_num_emu_prev_zeros = 0;
    ps_stream.u4_marker_bit = 0;

    // Call the function to fuzz
    impeg2d_dec_ac_coeff_zero(&ps_stream, &pu2_sym_len, &pu2_sym_val);
  }

  return 0;
}