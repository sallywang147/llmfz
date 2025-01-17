#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <vector>

extern "C" void isvce_evaluate_intra_4x4_modes(char * pu1_src, char * pu1_ngbr_pels, char * pu1_dst, int src_strd, int dst_strd, int u4_n_avblty, int * u4_intra_mode, int * pu4_sadmin, int u4_valid_intra_modes, int u4_lambda, int u4_predictd_mode);

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  if (size < 16) {
    return 0;
  }

  FuzzedDataProvider stream(data, size);

  // Create and initialize the parameters for isvce_evaluate_intra_4x4_modes
  std::vector<char> pu1_src = stream.ConsumeBytes<char>(4);
  std::vector<char> pu1_ngbr_pels = stream.ConsumeBytes<char>(4);
  std::vector<char> pu1_dst = stream.ConsumeBytes<char>(4);
  int src_strd = stream.ConsumeIntegral<int>();
  int dst_strd = stream.ConsumeIntegral<int>();
  int u4_n_avblty = stream.ConsumeIntegral<int>();
  int u4_intra_mode = stream.ConsumeIntegral<int>();
  int pu4_sadmin = stream.ConsumeIntegral<int>();
  int u4_valid_intra_modes = stream.ConsumeIntegral<int>();
  int u4_lambda = stream.ConsumeIntegral<int>();
  int u4_predictd_mode = stream.ConsumeIntegral<int>();

  // Call the function to fuzz
  isvce_evaluate_intra_4x4_modes(pu1_src.data(), pu1_ngbr_pels.data(), pu1_dst.data(), src_strd, dst_strd, u4_n_avblty, &u4_intra_mode, &pu4_sadmin, u4_valid_intra_modes, u4_lambda, u4_predictd_mode);

  return 0;
}