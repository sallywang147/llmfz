#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <string>

extern "C" {
#include "ihevce_enc_frm_proc_slave_thrd.h"
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  const size_t data_size = stream.ConsumeIntegralInRange<size_t>(0, size);
  const std::string data_string =
      stream.ConsumeBytesAsString(data_size);
  char* data_ptr = const_cast<char*>(data_string.c_str());
  ihevce_enc_frm_proc_slave_thrd(data_ptr, data_size);  // Add the size argument
  return 0;
}