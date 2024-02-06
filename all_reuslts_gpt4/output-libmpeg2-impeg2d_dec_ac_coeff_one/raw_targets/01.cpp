#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "impeg2d.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider provider(data, size);

  struct _stream_t stream;
  short sym_len = 0;
  short sym_val = 0;

  // Initialize stream
  if (provider.remaining_bytes() > 0) {
    size_t stream_size = provider.ConsumeIntegralInRange<size_t>(1, provider.remaining_bytes());
    auto stream_data = provider.ConsumeBytes<unsigned char>(stream_size);
    stream.u4_ofst = 0;
    stream.u4_max_ofst = stream_size * 8; // Convert byte size to bit size
    stream.pu1_buf = stream_data.data();
  } else {
    return 0; // Not enough data to initialize stream
  }

  impeg2d_dec_ac_coeff_one(&stream, &sym_len, &sym_val);
  
  return 0;
}