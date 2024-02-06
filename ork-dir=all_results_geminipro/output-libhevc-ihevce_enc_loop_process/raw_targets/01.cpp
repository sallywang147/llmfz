#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider provider(data, size);

  char* pv_ctxt = provider.ConsumeBytes<char>(provider.ConsumeIntegralInRange<size_t>(0, 1024));
  struct ihevce_lap_enc_buf_t* ps_curr_inp = nullptr;
  struct ctb_analyse_t* ps_ctb_in = nullptr;
  struct ipe_l0_ctb_analyse_for_me_t* ps_ipe_analyse = nullptr;
  struct recon_pic_buf_t* ps_frm_recon = nullptr;
  struct cur_ctb_cu_tree_t* ps_cu_tree_out = nullptr;
  struct ctb_enc_loop_out_t* ps_ctb_out = nullptr;
  struct cu_enc_loop_out_t* ps_cu_out = nullptr;
  struct tu_enc_loop_out_t* ps_tu_out = nullptr;
  struct pu_t* ps_pu_out = nullptr;
  char* pu1_frm_ecd_data = provider.ConsumeBytes<char>(provider.ConsumeIntegralInRange<size_t>(0, 1024));
  struct frm_ctb_ctxt_t* ps_frm_ctb_prms = nullptr;
  struct frm_lambda_ctxt_t* ps_frm_lamda = nullptr;
  struct multi_thrd_ctxt_t* ps_multi_thrd_ctxt = nullptr;
  int thrd_id = provider.ConsumeIntegral<int>();
  int i4_enc_frm_id = provider.ConsumeIntegral<int>();
  int i4_pass = provider.ConsumeIntegral<int>();

  ihevce_enc_loop_process(pv_ctxt, ps_curr_inp, ps_ctb_in, ps_ipe_analyse, ps_frm_recon, ps_cu_tree_out, ps_ctb_out, ps_cu_out, ps_tu_out, ps_pu_out, pu1_frm_ecd_data, ps_frm_ctb_prms, ps_frm_lamda, ps_multi_thrd_ctxt, thrd_id, i4_enc_frm_id, i4_pass);

  return 0;
}