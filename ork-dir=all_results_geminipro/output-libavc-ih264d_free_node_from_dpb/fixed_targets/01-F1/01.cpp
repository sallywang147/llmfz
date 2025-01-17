#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>

extern "C" {
#include "ih264d_dpb.h"
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  struct dpb_manager_t dpb_manager;
  dpb_manager_init(&dpb_manager);

  const int u4_cur_pic_num = stream.ConsumeIntegral<int>();
  const char u1_numRef_frames_for_seq =
      stream.ConsumeIntegralInRange<char>(0, 16);
  ih264d_free_node_from_dpb(&dpb_manager, u4_cur_pic_num,
                            u1_numRef_frames_for_seq);

  dpb_manager_deinit(&dpb_manager);
  return 0;
}