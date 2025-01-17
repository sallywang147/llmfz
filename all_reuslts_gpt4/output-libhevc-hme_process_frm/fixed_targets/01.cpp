#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>

#include "hme_interface.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  char pv_me_ctxt;
  pre_enc_L0_ipe_encloop_ctxt_t ps_l0_ipe_input;
  hme_ref_map_t ps_ref_map;
  double* intra_costs = nullptr;
  hme_frm_prms_t ps_frm_prms;
  func_type pf_ext_update_fxn = nullptr;
  char pv_coarse_layer;
  char pv_multi_thrd_ctxt;
  int i4_frame_parallelism_level = stream.ConsumeIntegral<int>();
  int thrd_id = stream.ConsumeIntegral<int>();
  int i4_me_frm_id = stream.ConsumeIntegral<int>();

  size_t size_of_intra_costs = stream.ConsumeIntegralInRange<size_t>(0, 100);
  intra_costs = new double[size_of_intra_costs];
  for (size_t i = 0; i < size_of_intra_costs; i++) {
    intra_costs[i] = stream.ConsumeFloatingPoint<double>();
  }

  double* ppd_intra_costs = intra_costs;

  hme_process_frm(&pv_me_ctxt, &ps_l0_ipe_input, &ps_ref_map, &ppd_intra_costs, &ps_frm_prms, pf_ext_update_fxn, &pv_coarse_layer, &pv_multi_thrd_ctxt, i4_frame_parallelism_level, thrd_id, i4_me_frm_id);

  delete[] intra_costs;

  return 0;
}