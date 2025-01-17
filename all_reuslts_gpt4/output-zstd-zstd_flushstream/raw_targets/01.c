#include <fuzzer/FuzzedDataProvider.h>
#include <zstd.h>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  // Create and initialize the ZSTD_CCtx
  ZSTD_CCtx* cctx = ZSTD_createCCtx();
  if (cctx == nullptr) {
    return 0;
  }

  // Create and initialize the ZSTD_inBuffer
  ZSTD_inBuffer inBuffer;
  inBuffer.size = stream.remaining_bytes();
  std::vector<uint8_t> buffer = stream.ConsumeRemainingBytes<uint8_t>();
  inBuffer.src = buffer.data();
  inBuffer.pos = 0;

  // Call the function to fuzz
  ZSTD_flushStream(cctx, &inBuffer);

  // Clean up
  ZSTD_freeCCtx(cctx);

  return 0;
}