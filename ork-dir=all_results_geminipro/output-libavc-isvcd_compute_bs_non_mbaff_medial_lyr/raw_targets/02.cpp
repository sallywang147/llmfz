#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <vector>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  struct _SvcDecLyrStruct ps_svc_lyr_dec;
  struct _DecMbInfo ps_cur_mb_info;
  short u2_mbxn_mb = stream.ConsumeIntegral<short>();
  isvcd_compute_bs_non_mbaff_medial_lyr(&ps_svc_lyr_dec, &ps_cur_mb_info,
                                        u2_mbxn_mb);
  return 0;
}