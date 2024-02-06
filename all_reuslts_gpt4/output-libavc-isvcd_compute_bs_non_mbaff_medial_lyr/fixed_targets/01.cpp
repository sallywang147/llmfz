#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "isvcd.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  struct _SvcDecLyrStruct svc_lyr_dec;
  struct _DecMbInfo cur_mb_info;

  // Consume data for svc_lyr_dec and cur_mb_info from the input
  size_t consumed_for_svc_lyr_dec = stream.ConsumeData(&svc_lyr_dec, sizeof(svc_lyr_dec));
  size_t consumed_for_cur_mb_info = stream.ConsumeData(&cur_mb_info, sizeof(cur_mb_info));

  // If we could not consume enough data for the structures, exit
  if (consumed_for_svc_lyr_dec < sizeof(svc_lyr_dec) || consumed_for_cur_mb_info < sizeof(cur_mb_info)) {
    return 0;
  }

  // Consume a short for u2_mbxn_mb
  short u2_mbxn_mb = stream.ConsumeIntegral<short>();

  // Call the function under test
  isvcd_compute_bs_non_mbaff_medial_lyr(&svc_lyr_dec, &cur_mb_info, u2_mbxn_mb);

  return 0;
}