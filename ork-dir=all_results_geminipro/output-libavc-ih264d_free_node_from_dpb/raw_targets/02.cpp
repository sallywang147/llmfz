#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>

#include "ih264d_dpb.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  const struct dpb_manager_t* ps_dpb_mgr =
      reinterpret_cast<const struct dpb_manager_t*>(stream.ConsumeIntegral<size_t>());
  const int u4_cur_pic_num = stream.ConsumeIntegral<int>();
  const char u1_numRef_frames_for_seq = stream.ConsumeIntegral<char>();
  ih264d_free_node_from_dpb(
      const_cast<struct dpb_manager_t*>(ps_dpb_mgr), u4_cur_pic_num,
      u1_numRef_frames_for_seq);
  return 0;
}