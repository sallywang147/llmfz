#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "tsk3/libtsk.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {

  FuzzedDataProvider stream(data, size);

  // Define and initialize a TSK_VS_PART_INFO object
  TSK_VS_PART_INFO a_part_info;
  a_part_info.tag = stream.ConsumeIntegral<uint32_t>();
  a_part_info.start = stream.ConsumeIntegral<uint64_t>();
  a_part_info.len = stream.ConsumeIntegral<uint64_t>();
  a_part_info.flags = stream.ConsumeIntegral<uint8_t>();
  a_part_info.slot_num = stream.ConsumeIntegral<uint32_t>();
  a_part_info.table_num = stream.ConsumeIntegral<uint32_t>();
  a_part_info.desc = stream.ConsumeBytesAsString(50).c_str();

  // Define and initialize a_ftype
  int a_ftype = stream.ConsumeIntegral<int>();

  // Call the function to fuzz
  struct TSK_FS_INFO *fs_info = tsk_fs_open_vol(&a_part_info, a_ftype);

  // Clean up
  if (fs_info != NULL) {
    tsk_fs_close(fs_info);
  }

  return 0;
}