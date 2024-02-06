#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>

extern "C" {
#include "ihevce_pre_enc_process_frame_thrd.h"
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  const size_t context_size = stream.ConsumeIntegralInRange<size_t>(
      0, 1024 * 1024);
  char* context = static_cast<char*>(malloc(context_size));
  stream.ConsumeBytes(context, context_size);
  int ret = ihevce_pre_enc_process_frame_thrd(context);
  free(context);
  return ret;
}