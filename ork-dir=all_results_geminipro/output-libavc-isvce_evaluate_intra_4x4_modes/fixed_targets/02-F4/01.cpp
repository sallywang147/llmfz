#include <fuzzer/FuzzedDataProvider.h>

#include <cstdint>
#include <cstdlib>
#include <vector>

extern "C" {
#include "isvce_encodings.h"
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  std::vector<char> pu1_src(16);
  stream.ConsumeBytes<char>(pu1_src.data(), pu1_src.size());
  std::vector<char> pu1_ngbr_pels(16);
  stream.ConsumeBytes<char>(pu1_ngbr_pels.data(), pu1_ngbr_pels.size());
  std::vector<char> pu1_dst(16);
  stream.ConsumeBytes<char>(pu1_dst.data(), pu1_dst.size());
  const int src_strd = stream.ConsumeIntegral<int>();
  const int dst_strd = stream.ConsumeIntegral<int>();
  const int u4_n_avblty = stream.ConsumeIntegral<int>();
  const int u4_intra_mode = stream.ConsumeIntegral<int>();
  const int pu4_sadmin = stream.ConsumeIntegral<int>();
  const int u4_valid_intra_modes = stream.ConsumeIntegral<int>();
  const int u4_lambda = stream.ConsumeIntegral<int>();
  const int u4_predictd_mode = stream.ConsumeIntegral<int>();

  isvce_evaluate_intra_4x4_modes(pu1_src.data(), pu1_ngbr_pels.data(), pu1_dst.data(), src_strd, dst_strd, u4_n_avblty, &u4_intra_mode, &pu4_sadmin, u4_valid_intra_modes, u4_lambda, u4_predictd_mode);
  return 0;
}