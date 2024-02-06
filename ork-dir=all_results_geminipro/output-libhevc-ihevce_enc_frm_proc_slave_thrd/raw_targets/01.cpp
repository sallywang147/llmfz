#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <string>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  const std::string input = stream.ConsumeRemainingBytesAsString();
  char* pv_frm_proc_thrd_ctxt = const_cast<char*>(input.c_str());
  int ret = ihevce_enc_frm_proc_slave_thrd(pv_frm_proc_thrd_ctxt);
  return ret;
}