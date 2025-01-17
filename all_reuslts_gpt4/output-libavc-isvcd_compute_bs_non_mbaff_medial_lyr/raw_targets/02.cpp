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
  short u2_mbxn_mb;

  // Consume data for struct _SvcDecLyrStruct
  size_t consumed = stream.ConsumeData(&svc_lyr_dec, sizeof(svc_lyr_dec));
  if (consumed != sizeof(svc_lyr_dec)) {
    return 0;
  }

  // Consume data for struct _DecMbInfo
  consumed = stream.ConsumeData(&cur_mb_info, sizeof(cur_mb_info));
  if (consumed != sizeof(cur_mb_info)) {
    return 0;
  }

  // Consume data for short u2_mbxn_mb
  u2_mbxn_mb = stream.ConsumeIntegral<short>();

  isvcd_compute_bs_non_mbaff_medial_lyr(&svc_lyr_dec, &cur_mb_info, u2_mbxn_mb);

  return 0;
}