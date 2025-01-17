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
  bool ai2_code_table = stream.ConsumeBool();
  bool au2_indexTable = stream.ConsumeBool();
  short u2_max_len = stream.ConsumeIntegral<short>();

  // Initialize ps_stream
  ps_stream.u4_ofst = stream.ConsumeIntegral<uint32_t>();
  ps_stream.pu1_buf = stream.ConsumeRemainingBytes<uint8_t>().data();

  impeg2d_fast_dec_vld_symbol(&ps_stream, ai2_code_table, au2_indexTable, u2_max_len);

  return 0;
}