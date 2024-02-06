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

  // We need at least 16 bytes for each of pu1_src, pu1_ngbr_pels, and pu1_dst.
  std::vector<char> src = stream.ConsumeBytes<char>(16);
  std::vector<char> ngbr_pels = stream.ConsumeBytes<char>(16);
  std::vector<char> dst = stream.ConsumeBytes<char>(16);

  int src_strd = stream.ConsumeIntegral<int>();
  int dst_strd = stream.ConsumeIntegral<int>();
  int n_avblty = stream.ConsumeIntegral<int>();

  int intra_mode = stream.ConsumeIntegral<int>();
  int sadmin = stream.ConsumeIntegral<int>();

  int valid_intra_modes = stream.ConsumeIntegral<int>();
  int lambda = stream.ConsumeIntegral<int>();
  int predictd_mode = stream.ConsumeIntegral<int>();

  isvce_evaluate_intra_4x4_modes(src.data(), ngbr_pels.data(), dst.data(), src_strd, dst_strd, n_avblty, &intra_mode, &sadmin, valid_intra_modes, lambda, predictd_mode);

  return 0;
}