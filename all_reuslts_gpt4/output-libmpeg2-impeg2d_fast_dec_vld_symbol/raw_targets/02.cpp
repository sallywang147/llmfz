#include <fuzzer/FuzzedDataProvider.h>
#include <cstddef>
#include <cstdint>
#include <vector>

extern "C" {
#include "impeg2d.h"
}

struct _stream_t {
  uint32_t u4_ofst;
  uint32_t u4_bit_ofst;
  uint8_t* pu1_buf;
  uint32_t u4_max_ofst;
};

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider stream(data, size);

  // Initialize the _stream_t structure
  struct _stream_t ps_stream;
  ps_stream.u4_ofst = stream.ConsumeIntegral<uint32_t>();
  ps_stream.u4_bit_ofst = stream.ConsumeIntegral<uint32_t>();
  std::vector<uint8_t> buf = stream.ConsumeRemainingBytes<uint8_t>();
  ps_stream.pu1_buf = buf.data();
  ps_stream.u4_max_ofst = buf.size();

  // Initialize other parameters
  bool ai2_code_table = stream.ConsumeBool();
  bool au2_indexTable = stream.ConsumeBool();
  short u2_max_len = stream.ConsumeIntegral<short>();

  // Call the function to fuzz
  impeg2d_fast_dec_vld_symbol(&ps_stream, ai2_code_table, au2_indexTable, u2_max_len);

  return 0;
}