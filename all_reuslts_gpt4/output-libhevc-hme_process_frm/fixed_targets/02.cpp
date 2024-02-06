#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <vector>

#include "hme_process_frm.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  char pv_me_ctxt = stream.ConsumeIntegral<char>();
  struct pre_enc_L0_ipe_encloop_ctxt_t ps_l0_ipe_input;
  struct hme_ref_map_t ps_ref_map;
  double* pd_intra_costs = new double[1];
  pd_intra_costs[0] = stream.ConsumeFloatingPoint<double>();
  double** ppd_intra_costs = &pd_intra_costs;
  struct hme_frm_prms_t ps_frm_prms;
  func_type pf_ext_update_fxn = nullptr; // Assuming no function pointer is available for fuzzing
  char pv_coarse_layer = stream.ConsumeIntegral<char>();
  char pv_multi_thrd_ctxt = stream.ConsumeIntegral<char>();
  int i4_frame_parallelism_level = stream.ConsumeIntegral<int>();
  int thrd_id = stream.ConsumeIntegral<int>();
  int i4_me_frm_id = stream.ConsumeIntegral<int>();

  hme_process_frm(&pv_me_ctxt, &ps_l0_ipe_input, &ps_ref_map, ppd_intra_costs, &ps_frm_prms, pf_ext_update_fxn, &pv_coarse_layer, &pv_multi_thrd_ctxt, i4_frame_parallelism_level, thrd_id, i4_me_frm_id);

  delete[] pd_intra_costs;
  return 0;
}