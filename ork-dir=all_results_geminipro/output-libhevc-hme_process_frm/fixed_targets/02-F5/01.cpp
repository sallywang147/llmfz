#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <string>

extern "C" {
#include "hme_process_frm.h"
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  char* pv_me_ctxt = stream.ConsumeBytes<char>(stream.ConsumeIntegralInRange(0, 1024));
  struct pre_enc_L0_ipe_encloop_ctxt_t* ps_l0_ipe_input =
      reinterpret_cast<struct pre_enc_L0_ipe_encloop_ctxt_t*>(
          stream.ConsumeBytes<uint8_t>(stream.ConsumeIntegralInRange(0, 1024))
              .data());
  struct hme_ref_map_t* ps_ref_map =
      reinterpret_cast<struct hme_ref_map_t*>(
          stream.ConsumeBytes<uint8_t>(stream.ConsumeIntegralInRange(0, 1024))
              .data());
  double** ppd_intra_costs =
      reinterpret_cast<double**>(
          stream.ConsumeBytes<uint8_t>(stream.ConsumeIntegralInRange(0, 1024))
              .data());
  struct hme_frm_prms_t* ps_frm_prms =
      reinterpret_cast<struct hme_frm_prms_t*>(
          stream.ConsumeBytes<uint8_t>(stream.ConsumeIntegralInRange(0, 1024))
              .data());
  func_type pf_ext_update_fxn =
      reinterpret_cast<func_type>(
          stream.ConsumeBytes<uint8_t>(stream.ConsumeIntegralInRange(0, 1024))
              .data());
  char* pv_coarse_layer = stream.ConsumeBytes<char>(stream.ConsumeIntegralInRange(0, 1024)).data();
  char* pv_multi_thrd_ctxt = stream.ConsumeBytes<char>(stream.ConsumeIntegralInRange(0, 1024)).data();
  int i4_frame_parallelism_level = stream.ConsumeIntegral<int>();
  int thrd_id = stream.ConsumeIntegral<int>();
  int i4_me_frm_id = stream.ConsumeIntegral<int>();

  hme_process_frm(pv_me_ctxt, ps_l0_ipe_input, ps_ref_map, ppd_intra_costs, ps_frm_prms,
                  pf_ext_update_fxn, pv_coarse_layer, pv_multi_thrd_ctxt,
                  i4_frame_parallelism_level, thrd_id, i4_me_frm_id);
  return 0;
}