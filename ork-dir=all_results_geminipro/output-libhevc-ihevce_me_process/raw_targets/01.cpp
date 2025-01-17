#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <string>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  const size_t pv_me_ctxt_size = stream.ConsumeIntegralInRange<size_t>(0, 1024);
  char* pv_me_ctxt = new char[pv_me_ctxt_size];
  stream.ConsumeBytes(pv_me_ctxt, pv_me_ctxt_size);
  const size_t ps_enc_lap_inp_size =
      stream.ConsumeIntegralInRange<size_t>(0, 1024);
  struct ihevce_lap_enc_buf_t* ps_enc_lap_inp =
      new struct ihevce_lap_enc_buf_t[ps_enc_lap_inp_size];
  stream.ConsumeBytes(reinterpret_cast<uint8_t*>(ps_enc_lap_inp),
                      ps_enc_lap_inp_size * sizeof(*ps_enc_lap_inp));
  const size_t ps_ctb_out_size = stream.ConsumeIntegralInRange<size_t>(0, 1024);
  struct ctb_analyse_t* ps_ctb_out =
      new struct ctb_analyse_t[ps_ctb_out_size];
  stream.ConsumeBytes(reinterpret_cast<uint8_t*>(ps_ctb_out),
                      ps_ctb_out_size * sizeof(*ps_ctb_out));
  const size_t ps_cur_out_me_prms_size =
      stream.ConsumeIntegralInRange<size_t>(0, 1024);
  struct me_enc_rdopt_ctxt_t* ps_cur_out_me_prms =
      new struct me_enc_rdopt_ctxt_t[ps_cur_out_me_prms_size];
  stream.ConsumeBytes(reinterpret_cast<uint8_t*>(ps_cur_out_me_prms),
                      ps_cur_out_me_prms_size * sizeof(*ps_cur_out_me_prms));
  const size_t pd_intra_costs_size =
      stream.ConsumeIntegralInRange<size_t>(0, 1024);
  double* pd_intra_costs = new double[pd_intra_costs_size];
  stream.ConsumeBytes(reinterpret_cast<uint8_t*>(pd_intra_costs),
                      pd_intra_costs_size * sizeof(*pd_intra_costs));
  const size_t ps_ipe_analyse_ctb_size =
      stream.ConsumeIntegralInRange<size_t>(0, 1024);
  struct ipe_l0_ctb_analyse_for_me_t* ps_ipe_analyse_ctb =
      new struct ipe_l0_ctb_analyse_for_me_t[ps_ipe_analyse_ctb_size];
  stream.ConsumeBytes(reinterpret_cast<uint8_t*>(ps_ipe_analyse_ctb),
                      ps_ipe_analyse_ctb_size * sizeof(*ps_ipe_analyse_ctb));
  const size_t ps_l0_ipe_input_size =
      stream.ConsumeIntegralInRange<size_t>(0, 1024);
  struct pre_enc_L0_ipe_encloop_ctxt_t* ps_l0_ipe_input =
      new struct pre_enc_L0_ipe_encloop_ctxt_t[ps_l0_ipe_input_size];
  stream.ConsumeBytes(reinterpret_cast<uint8_t*>(ps_l0_ipe_input),
                      ps_l0_ipe_input_size * sizeof(*ps_l0_ipe_input));
  const size_t pv_coarse_layer_size =
      stream.ConsumeIntegralInRange<size_t>(0, 1024);
  char* pv_coarse_layer = new char[pv_coarse_layer_size];
  stream.ConsumeBytes(pv_coarse_layer, pv_coarse_layer_size);
  const size_t ps_multi_thrd_ctxt_size =
      stream.ConsumeIntegralInRange<size_t>(0, 1024);
  struct multi_thrd_ctxt_t* ps_multi_thrd_ctxt =
      new struct multi_thrd_ctxt_t[ps_multi_thrd_ctxt_size];
  stream.ConsumeBytes(reinterpret_cast<uint8_t*>(ps_multi_thrd_ctxt),
                      ps_multi_thrd_ctxt_size * sizeof(*ps_multi_thrd_ctxt));
  const int i4_frame_parallelism_level =
      stream.ConsumeIntegralInRange<int>(-100, 100);
  const int thrd_id = stream.ConsumeIntegralInRange<int>(-100, 100);
  const int i4_me_frm_id = stream.ConsumeIntegralInRange<int>(-100, 100);

  ihevce_me_process(pv_me_ctxt, ps_enc_lap_inp, ps_ctb_out, ps_cur_out_me_prms,
                     pd_intra_costs, ps_ipe_analyse_ctb, ps_l0_ipe_input,
                     pv_coarse_layer, ps_multi_thrd_ctxt, i4_frame_parallelism_level,
                     thrd_id, i4_me_frm_id);

  delete[] pv_me_ctxt;
  delete[] ps_enc_lap_inp;
  delete[] ps_ctb_out;
  delete[] ps_cur_out_me_prms;
  delete[] pd_intra_costs;
  delete[] ps_ipe_analyse_ctb;
  delete[] ps_l0_ipe_input;
  delete[] pv_coarse_layer;
  delete[] ps_multi_thrd_ctxt;

  return 0;
}