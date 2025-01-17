#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>

#include "ihevce_api.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  char pv_ctxt;
  struct ihevce_lap_enc_buf_t ps_curr_inp;
  struct ctb_analyse_t ps_ctb_in;
  struct ipe_l0_ctb_analyse_for_me_t ps_ipe_analyse;
  struct recon_pic_buf_t ps_frm_recon;
  struct cur_ctb_cu_tree_t ps_cu_tree_out;
  struct ctb_enc_loop_out_t ps_ctb_out;
  struct cu_enc_loop_out_t ps_cu_out;
  struct tu_enc_loop_out_t ps_tu_out;
  struct pu_t ps_pu_out;
  char pu1_frm_ecd_data;
  struct frm_ctb_ctxt_t ps_frm_ctb_prms;
  struct frm_lambda_ctxt_t ps_frm_lamda;
  struct multi_thrd_ctxt_t ps_multi_thrd_ctxt;
  int thrd_id = stream.ConsumeIntegral<int>();
  int i4_enc_frm_id = stream.ConsumeIntegral<int>();
  int i4_pass = stream.ConsumeIntegral<int>();

  // Consume data for each struct
  stream.ConsumeData(&ps_curr_inp, sizeof(ps_curr_inp));
  stream.ConsumeData(&ps_ctb_in, sizeof(ps_ctb_in));
  stream.ConsumeData(&ps_ipe_analyse, sizeof(ps_ipe_analyse));
  stream.ConsumeData(&ps_frm_recon, sizeof(ps_frm_recon));
  stream.ConsumeData(&ps_cu_tree_out, sizeof(ps_cu_tree_out));
  stream.ConsumeData(&ps_ctb_out, sizeof(ps_ctb_out));
  stream.ConsumeData(&ps_cu_out, sizeof(ps_cu_out));
  stream.ConsumeData(&ps_tu_out, sizeof(ps_tu_out));
  stream.ConsumeData(&ps_pu_out, sizeof(ps_pu_out));
  stream.ConsumeData(&ps_frm_ctb_prms, sizeof(ps_frm_ctb_prms));
  stream.ConsumeData(&ps_frm_lamda, sizeof(ps_frm_lamda));
  stream.ConsumeData(&ps_multi_thrd_ctxt, sizeof(ps_multi_thrd_ctxt));

  // Call the function to fuzz
  ihevce_enc_loop_process(&pv_ctxt, &ps_curr_inp, &ps_ctb_in, &ps_ipe_analyse, &ps_frm_recon, &ps_cu_tree_out, &ps_ctb_out, &ps_cu_out, &ps_tu_out, &ps_pu_out, &pu1_frm_ecd_data, &ps_frm_ctb_prms, &ps_frm_lamda, &ps_multi_thrd_ctxt, thrd_id, i4_enc_frm_id, i4_pass);

  return 0;
}