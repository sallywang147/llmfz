#include <fuzzer/FuzzedDataProvider.h>
#include <cstddef>
#include <cstdint>

extern "C" int ihevce_enc_frm_proc_slave_thrd(char * pv_frm_proc_thrd_ctxt);

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider stream(data, size);

  // Extract a string. You MUST use .c_str() to use result as pointer
  std::string str = stream.ConsumeRemainingBytesAsString();
  char *pv_frm_proc_thrd_ctxt = const_cast<char*>(str.c_str());

  // Call the function with the fuzzed input.
  ihevce_enc_frm_proc_slave_thrd(pv_frm_proc_thrd_ctxt);

  return 0;
}