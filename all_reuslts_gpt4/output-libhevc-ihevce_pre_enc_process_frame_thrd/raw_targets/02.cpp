#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>

#include "ihevce_pre_enc_process_frame_thrd.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  // Define a buffer to hold the data for the function
  std::string buffer = stream.ConsumeRemainingBytesAsString();
  
  // Call the function with the fuzzed data
  ihevce_pre_enc_process_frame_thrd(buffer.data());

  return 0;
}