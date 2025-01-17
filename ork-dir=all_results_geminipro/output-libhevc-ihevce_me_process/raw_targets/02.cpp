#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <string>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  const size_t pv_me_ctxt_size = stream.ConsumeIntegralInRange<size_t>(0, 1024);
  char* pv_me_ctxt = static_cast<char*>(std::malloc(pv_me_ctxt_size));
  stream.ConsumeBytes(pv_me_ctxt, pv_me_ctxt_size);
  const size_t ps_enc_lap_inp_size =
      stream.ConsumeIntegralInRange<size_t>(0, 1024);
  struct ihevce_lap_enc_buf_t* ps_enc_lap_inp =
      static_cast<struct ihevce_lap_enc_buf_t*>(
          std::malloc(ps_enc_lap_inp_size));
  stream.ConsumeBytes(ps_enc_lap_inp, ps_enc_lap_inp_size);
  const size_t ps_ctb_out_size = stream.ConsumeIntegralInRange<size_t>(0, 1024);
  struct ctb_analyse_t* ps_ctb_out =
      static_cast<struct ctb_analyse_t*>(std::malloc(ps_ctb_out_size));
  stream.ConsumeBytes(ps_ctb_out, ps_ctb_out_size);
  const size_t ps_cur_out_me_prms_size =
      stream.ConsumeIntegralInRange<size_t>(0, 1024);
  struct me_enc_rdopt_ctxt_t* ps_cur_out_me_prms =
      static_cast<struct me_enc_rdopt_ctxt_t*>(
          std::malloc(ps_cur_out_me_prms_size));
  stream.ConsumeBytes(ps_cur_out_me_prms, ps_cur_out_me_prms_size);
  const size_t pd_intra_costs_size = stream.ConsumeIntegralInRange<size_t>(0, 1024);
  double* pd_intra_costs =
      static_cast<double*>(std::malloc(pd_intra_costs_size));
  stream.ConsumeBytes(pd_intra_costs, pd_intra_costs_size);
  const size_t ps_ipe_analyse_ctb_size =
      stream.ConsumeIntegralInRange<size_t>(0, 1024);
  struct ipe_l0_ctb_analyse_for_me_t* ps_ipe_analyse_ctb =
      static_cast<struct ipe_l0_ctb_analyse_for_me_t*>(
          std::malloc(ps_ipe_analyse_ctb_size));
  stream.ConsumeBytes(ps_ipe_analyse_ctb, ps_ipe_analyse_ctb_size);
  const size_t ps_l0_ipe_input_size =
      stream.ConsumeIntegralInRange<size_t>(0, 1024);
  struct pre_enc_L0_ipe_encloop_ctxt_t* ps_l0_ipe_input =
      static_cast<struct pre_enc_L0_ipe_encloop_ctxt_t*>(
          std::malloc(ps_l0_ipe_input_size));
  stream.ConsumeBytes(ps_l0_ipe_input, ps_l0_ipe_input_size);
  const size_t pv_coarse_layer_size =
      stream.ConsumeIntegralInRange<size_t>(0, 1024);
  char* pv_coarse_layer =
      static_cast<char*>(std::malloc(pv_coarse_layer_size));
  stream.ConsumeBytes(pv_coarse_layer, pv_coarse_layer_size);
  const size_t ps_multi_thrd_ctxt_size =
      stream.ConsumeIntegralInRange<size_t>(0, 1024);
  struct multi_thrd_ctxt_t* ps_multi_thrd_ctxt =
      static_cast<struct multi_thrd_ctxt_t*>(
          std::malloc(ps_multi_thrd_ctxt_size));
  stream.ConsumeBytes(ps_multi_thrd_ctxt, ps_multi_thrd_ctxt_size);
  const int i4_frame_parallelism_level =
      stream.ConsumeIntegral<int>();
  const int thrd_id = stream.ConsumeIntegral<int>();
  const int i4_me_frm_id = stream.ConsumeIntegral<int>();

  ihevce_me_process(pv_me_ctxt, ps_enc_lap_inp, ps_ctb_out,
                     ps_cur_out_me_prms, pd_intra_costs, ps_ipe_analyse_ctb,
                     ps_l0_ipe_input, pv_coarse_layer, ps_multi_thrd_ctxt,
                     i4_frame_parallelism_level, thrd_id, i4_me_frm_id);
  std::free(pv_me_ctxt);
  std::free(ps_enc_lap_inp);
  std::free(ps_ctb_out);
  std::free(ps_cur_out_me_prms);
  std::free(pd_intra_costs);
  std::free(ps_ipe_analyse_ctb);
  std::free(ps_l0_ipe_input);
  std::free(pv_coarse_layer);
  std::free(ps_multi_thrd_ctxt);
  return 0;
}