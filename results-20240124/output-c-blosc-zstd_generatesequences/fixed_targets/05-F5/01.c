#include <algorithm>
#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <string>

#include "zstd.h"

extern "C" {
#include "lz4hc.h"
#include "fuzzer.h" // Include the fuzzer header
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  struct ZSTD_CCtx_s* cctx = ZSTD_createCCtx();
  if (cctx == nullptr) {
    return 0;
  }
  struct LZ4HC_optimal_t* opt = LZ4HC_createOptimal();
  if (opt == nullptr) {
    ZSTD_freeCCtx(cctx);
    return 0;
  }

  const size_t in_size = stream.ConsumeIntegral<size_t>();
  std::string in_str = stream.ConsumeRemainingBytesAsString();
  if (in_str.size() != in_size) {
    LZ4HC_freeOptimal(opt);
    ZSTD_freeCCtx(cctx);
    return 0;
  }
  const char* in_data = in_str.c_str();

  const size_t out_size = stream.ConsumeIntegral<size_t>();
  std::string out_str(out_size, '\0');
  char* out_data = const_cast<char*>(out_str.c_str());

  size_t zstd_ret = ZSTD_generateSequences(cctx, opt, in_size, in_data, out_size, out_data);
  if (ZSTD_isError(zstd_ret)) {
    LZ4HC_freeOptimal(opt);
    ZSTD_freeCCtx(cctx);
    return 0;
  }

  LZ4HC_freeOptimal(opt);
  ZSTD_freeCCtx(cctx);

  return 0;
}