#include <fuzzer/FuzzedDataProvider.h>
#include <zstd.h>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider stream(data, size);

  // Initialize compression context
  ZSTD_CCtx* cctx = ZSTD_createCCtx();
  if (cctx == nullptr) {
    return 0;
  }

  // Prepare input buffer
  size_t inputSize = stream.remaining_bytes();
  std::vector<uint8_t> inputBuffer = stream.ConsumeRemainingBytes<uint8_t>();
  ZSTD_inBuffer inBuffer = {inputBuffer.data(), inputSize, 0};

  // Call the function to fuzz
  ZSTD_endStream(cctx, &inBuffer);

  // Clean up
  ZSTD_freeCCtx(cctx);

  return 0;
}