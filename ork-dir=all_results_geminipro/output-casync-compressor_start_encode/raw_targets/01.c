#include <fuzz.h>
#include <compressor.h>
#include <log.h>
#include <stdlib.h>

int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  _cleanup_(compressor_finish) CompressorContext c = COMPRESSOR_CONTEXT_INIT;

  if (size < 1)
    return 0;

  FuzzedDataProvider stream(data, size);
  int compressor = stream.ConsumeIntegralInRange<int>(0, 100);

  int r = compressor_start_encode(&c, compressor);
  if (r < 0) {
    log_debug_errno(r, "compressor_start_encode failed: %m");
    return 0;
  }

  return 0;
}