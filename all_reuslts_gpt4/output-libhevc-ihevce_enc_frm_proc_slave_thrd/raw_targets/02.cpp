#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

extern "C" int ihevce_enc_frm_proc_slave_thrd(char * pv_frm_proc_thrd_ctxt);

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  // Consume all remaining bytes as a string.
  std::string str = stream.ConsumeRemainingBytesAsString();
  char *pv_frm_proc_thrd_ctxt = const_cast<char*>(str.c_str());

  ihevce_enc_frm_proc_slave_thrd(pv_frm_proc_thrd_ctxt);

  return 0;
}