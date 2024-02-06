#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "ih264d_structs.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  // Initialize dpb_manager_t struct
  struct dpb_manager_t ps_dpb_mgr;
  ps_dpb_mgr.u1_num_of_ref_frames = stream.ConsumeIntegral<unsigned char>();
  ps_dpb_mgr.u2_max_pic_width = stream.ConsumeIntegral<unsigned short>();
  ps_dpb_mgr.u2_max_frm_ht = stream.ConsumeIntegral<unsigned short>();
  ps_dpb_mgr.u2_max_pic_ht = stream.ConsumeIntegral<unsigned short>();
  ps_dpb_mgr.u2_max_dpb_size = stream.ConsumeIntegral<unsigned short>();
  ps_dpb_mgr.u2_max_ref_buff_cnt = stream.ConsumeIntegral<unsigned short>();
  ps_dpb_mgr.u2_max_dpb_num = stream.ConsumeIntegral<unsigned short>();
  ps_dpb_mgr.u2_max_dpb_size_mbs = stream.ConsumeIntegral<unsigned short>();
  ps_dpb_mgr.u2_max_pic_size_mbs = stream.ConsumeIntegral<unsigned short>();
  ps_dpb_mgr.u2_max_frm_size_mbs = stream.ConsumeIntegral<unsigned short>();
  ps_dpb_mgr.u2_max_wd_mbs = stream.ConsumeIntegral<unsigned short>();
  ps_dpb_mgr.u2_max_ht_mbs = stream.ConsumeIntegral<unsigned short>();
  ps_dpb_mgr.u2_max_wd = stream.ConsumeIntegral<unsigned short>();
  ps_dpb_mgr.u2_max_ht = stream.ConsumeIntegral<unsigned short>();
  ps_dpb_mgr.u4_max_yuv_buf_size = stream.ConsumeIntegral<unsigned int>();
  ps_dpb_mgr.u4_max_yuv_strd = stream.ConsumeIntegral<unsigned int>();
  ps_dpb_mgr.u4_max_yuv_ht = stream.ConsumeIntegral<unsigned int>();
  ps_dpb_mgr.u4_max_yuv_wd = stream.ConsumeIntegral<unsigned int>();

  // Initialize other parameters
  int u4_cur_pic_num = stream.ConsumeIntegral<int>();
  char u1_numRef_frames_for_seq = stream.ConsumeIntegral<char>();

  // Call the target function
  ih264d_free_node_from_dpb(&ps_dpb_mgr, u4_cur_pic_num, u1_numRef_frames_for_seq);

  return 0;
}