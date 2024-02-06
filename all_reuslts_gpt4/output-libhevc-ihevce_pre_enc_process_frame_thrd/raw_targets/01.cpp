#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>

#include "ihevce_api.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  // Extract a string. You MUST use .c_str() to use result as pointer
  std::string str = stream.ConsumeRandomLengthString();
  char *pv_frm_proc_thrd_ctxt = const_cast<char *>(str.c_str());

  // Call the function to fuzz
  ihevce_pre_enc_process_frame_thrd(pv_frm_proc_thrd_ctxt);

  return 0;
}