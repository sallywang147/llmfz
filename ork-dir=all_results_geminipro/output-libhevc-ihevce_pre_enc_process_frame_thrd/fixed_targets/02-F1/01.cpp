#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <string>

extern "C" {
#include "ihevce_pre_enc_process_frame_thrd.h"
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  const std::string ctxt = stream.ConsumeRemainingBytesAsString();
  char* pv_frm_proc_thrd_ctxt = const_cast<char*>(ctxt.c_str());
  int ret = ihevce_pre_enc_process_frame_thrd(pv_frm_proc_thrd_ctxt);
  return ret;
}