#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

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
  struct frm_ctb_ctxt_t ps_frm_ctb_prms;
  struct frm_lambda_ctxt_t ps_frm_lamda;
  struct multi_thrd_ctxt_t ps_multi_thrd_ctxt;

  size_t pv_ctxt_size = stream.ConsumeIntegralInRange<size_t>(0, size);
  pv_ctxt = *stream.ConsumeBytesAsString(pv_ctxt_size).c_str();

  size_t ps_curr_inp_size = stream.ConsumeIntegralInRange<size_t>(0, size);
  stream.ConsumeData(&ps_curr_inp, ps_curr_inp_size);

  size_t ps_ctb_in_size = stream.ConsumeIntegralInRange<size_t>(0, size);
  stream.ConsumeData(&ps_ctb_in, ps_ctb_in_size);

  size_t ps_ipe_analyse_size = stream.ConsumeIntegralInRange<size_t>(0, size);
  stream.ConsumeData(&ps_ipe_analyse, ps_ipe_analyse_size);

  size_t ps_frm_recon_size = stream.ConsumeIntegralInRange<size_t>(0, size);
  stream.ConsumeData(&ps_frm_recon, ps_frm_recon_size);

  size_t ps_cu_tree_out_size = stream.ConsumeIntegralInRange<size_t>(0, size);
  stream.ConsumeData(&ps_cu_tree_out, ps_cu_tree_out_size);

  size_t ps_ctb_out_size = stream.ConsumeIntegralInRange<size_t>(0, size);
  stream.ConsumeData(&ps_ctb_out, ps_ctb_out_size);

  size_t ps_cu_out_size = stream.ConsumeIntegralInRange<size_t>(0, size);
  stream.ConsumeData(&ps_cu_out, ps_cu_out_size);

  size_t ps_tu_out_size = stream.ConsumeIntegralInRange<size_t>(0, size);
  stream.ConsumeData(&ps_tu_out, ps_tu_out_size);

  size_t ps_pu_out_size = stream.ConsumeIntegralInRange<size_t>(0, size);
  stream.ConsumeData(&ps_pu_out, ps_pu_out_size);

  size_t ps_frm_ctb_prms_size = stream.ConsumeIntegralInRange<size_t>(0, size);
  stream.ConsumeData(&ps_frm_ctb_prms, ps_frm_ctb_prms_size);

  size_t ps_frm_lamda_size = stream.ConsumeIntegralInRange<size_t>(0, size);
  stream.ConsumeData(&ps_frm_lamda, ps_frm_lamda_size);

  size_t ps_multi_thrd_ctxt_size = stream.ConsumeIntegralInRange<size_t>(0, size);
  stream.ConsumeData(&ps_multi_thrd_ctxt, ps_multi_thrd_ctxt_size);

  int thrd_id = stream.ConsumeIntegral<int>();
  int i4_enc_frm_id = stream.ConsumeIntegral<int>();
  int i4_pass = stream.ConsumeIntegral<int>();

  size_t pu1_frm_ecd_data_size = stream.ConsumeIntegralInRange<size_t>(0, size);
  char *pu1_frm_ecd_data = stream.ConsumeBytesAsString(pu1_frm_ecd_data_size).c_str();

  ihevce_enc_loop_process(&pv_ctxt, &ps_curr_inp, &ps_ctb_in, &ps_ipe_analyse, &ps_frm_recon, &ps_cu_tree_out, &ps_ctb_out, &ps_cu_out, &ps_tu_out, &ps_pu_out, pu1_frm_ecd_data, &ps_frm_ctb_prms, &ps_frm_lamda, &ps_multi_thrd_ctxt, thrd_id, i4_enc_frm_id, i4_pass);

  return 0;
}