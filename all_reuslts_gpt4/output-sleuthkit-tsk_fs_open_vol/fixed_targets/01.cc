#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "tsk/libtsk.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  // Create a dummy TSK_VS_PART_INFO struct
  TSK_VS_PART_INFO a_part_info;
  a_part_info.tag = TSK_VS_PART_INFO_TAG;
  a_part_info.addr = stream.ConsumeIntegral<uint8_t>();
  a_part_info.start = stream.ConsumeIntegral<uint64_t>();
  a_part_info.len = stream.ConsumeIntegral<uint64_t>();
  a_part_info.flags = (TSK_VS_PART_FLAG_ENUM)stream.ConsumeIntegral<uint8_t>();
  a_part_info.table_num = stream.ConsumeIntegral<uint8_t>();
  a_part_info.slot_num = stream.ConsumeIntegral<uint8_t>();

  // Consume the rest of the data as the file system type
  int a_ftype = stream.ConsumeIntegral<int>();

  // Call the function to fuzz
  TSK_FS_INFO * fs_info = tsk_fs_open_vol(&a_part_info, a_ftype);

  // Clean up
  if (fs_info != nullptr) {
    tsk_fs_close(fs_info);
  }

  return 0;
}