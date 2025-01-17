#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <vector>

#include "ihevce_me_process.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  char pv_me_ctxt = stream.ConsumeIntegral<char>();
  struct ihevce_lap_enc_buf_t ps_enc_lap_inp;
  struct ctb_analyse_t ps_ctb_out;
  struct me_enc_rdopt_ctxt_t ps_cur_out_me_prms;
  double pd_intra_costs = stream.ConsumeFloatingPoint<double>();
  struct ipe_l0_ctb_analyse_for_me_t ps_ipe_analyse_ctb;
  struct pre_enc_L0_ipe_encloop_ctxt_t ps_l0_ipe_input;
  char pv_coarse_layer = stream.ConsumeIntegral<char>();
  struct multi_thrd_ctxt_t ps_multi_thrd_ctxt;
  int i4_frame_parallelism_level = stream.ConsumeIntegral<int>();
  int thrd_id = stream.ConsumeIntegral<int>();
  int i4_me_frm_id = stream.ConsumeIntegral<int>();

  ihevce_me_process(&pv_me_ctxt, &ps_enc_lap_inp, &ps_ctb_out, &ps_cur_out_me_prms, &pd_intra_costs, &ps_ipe_analyse_ctb, &ps_l0_ipe_input, &pv_coarse_layer, &ps_multi_thrd_ctxt, i4_frame_parallelism_level, thrd_id, i4_me_frm_id);

  return 0;
}