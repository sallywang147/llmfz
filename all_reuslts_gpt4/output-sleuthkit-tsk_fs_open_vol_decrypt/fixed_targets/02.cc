#include <fuzzer/FuzzedDataProvider.h>
#include <tsk/libtsk.h>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider stream(data, size);

  // Create a dummy TSK_VS_PART_INFO
  TSK_VS_PART_INFO a_part_info = {0};

  // Extract an integer value for a_ftype
  int a_ftype = stream.ConsumeIntegral<int>();

  // Extract a string for a_pass. You MUST use .c_str() to use result as pointer
  std::string a_pass = stream.ConsumeRandomLengthString();
  
  // Call the target function
  TSK_FS_INFO *fs_info = tsk_fs_open_vol_decrypt(&a_part_info, a_ftype, const_cast<char*>(a_pass.c_str()));

  // If fs_info is not NULL, it means the function succeeded, so we need to close it.
  if (fs_info != nullptr) {
    tsk_fs_close(fs_info);
  }

  return 0;
}