#include <fuzzer/FuzzedDataProvider.h>
#include <cstddef>
#include <cstdint>
#include <cstdlib>

extern "C" {
#include "impeg2_jobq.h"
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  struct jobq_t* ps_jobq = reinterpret_cast<struct jobq_t*>(
      stream.ConsumeBytes<uint8_t>(stream.ConsumeIntegral<size_t>()));
  impeg2_jobq_free(ps_jobq);
  return 0;
}