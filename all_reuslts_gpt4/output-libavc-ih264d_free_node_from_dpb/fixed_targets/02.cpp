#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "ih264d.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  // Define and initialize the parameters for ih264d_free_node_from_dpb
  struct dpb_manager_t ps_dpb_mgr;
  int u4_cur_pic_num = stream.ConsumeIntegral<int>();
  char u1_numRef_frames_for_seq = stream.ConsumeIntegral<char>();

  // Call the function with the defined parameters
  int result = ih264d_free_node_from_dpb(&ps_dpb_mgr, u4_cur_pic_num, u1_numRef_frames_for_seq);

  return 0;
}