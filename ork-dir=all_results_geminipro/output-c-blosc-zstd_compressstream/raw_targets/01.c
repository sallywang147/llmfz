#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <string>

#include "zstd.h"

extern "C" size_t LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  const uint8_t compression_level = stream.ConsumeIntegral<uint8_t>();
  const uint8_t window_log = stream.ConsumeIntegral<uint8_t>();
  const uint8_t hash_log = stream.ConsumeIntegral<uint8_t>();
  const uint8_t chain_log = stream.ConsumeIntegral<uint8_t>();
  const uint8_t search_log = stream.ConsumeIntegral<uint8_t>();
  const uint8_t min_match = stream.ConsumeIntegral<uint8_t>();
  const uint8_t target_length = stream.ConsumeIntegral<uint8_t>();
  const uint8_t strategy = stream.ConsumeIntegral<uint8_t>();

  ZSTD_CCtx* const cctx = ZSTD_createCCtx();
  if (cctx == nullptr) {
    return 0;
  }

  size_t const init_result = ZSTD_CCtx_setParameter(cctx, ZSTD_c_compressionLevel,
                                                   compression_level);
  if (ZSTD_isError(init_result)) {
    ZSTD_freeCCtx(cctx);
    return 0;
  }

  size_t const window_log_result = ZSTD_CCtx_setParameter(cctx, ZSTD_c_windowLog,
                                                         window_log);
  if (ZSTD_isError(window_log_result)) {
    ZSTD_freeCCtx(cctx);
    return 0;
  }

  size_t const hash_log_result = ZSTD_CCtx_setParameter(cctx, ZSTD_c_hashLog,
                                                       hash_log);
  if (ZSTD_isError(hash_log_result)) {
    ZSTD_freeCCtx(cctx);
    return 0;
  }

  size_t const chain_log_result = ZSTD_CCtx_setParameter(cctx, ZSTD_c_chainLog,
                                                       chain_log);
  if (ZSTD_isError(chain_log_result)) {
    ZSTD_freeCCtx(cctx);
    return 0;
  }

  size_t const search_log_result = ZSTD_CCtx_setParameter(cctx, ZSTD_c_searchLog,
                                                         search_log);
  if (ZSTD_isError(search_log_result)) {
    ZSTD_freeCCtx(cctx);
    return 0;
  }

  size_t const min_match_result = ZSTD_CCtx_setParameter(cctx, ZSTD_c_minMatch,
                                                        min_match);
  if (ZSTD_isError(min_match_result)) {
    ZSTD_freeCCtx(cctx);
    return 0;
  }

  size_t const target_length_result = ZSTD_CCtx_setParameter(cctx, ZSTD_c_targetLength,
                                                           target_length);
  if (ZSTD_isError(target_length_result)) {
    ZSTD_freeCCtx(cctx);
    return 0;
  }

  size_t const strategy_result = ZSTD_CCtx_setParameter(cctx, ZSTD_c_strategy,
                                                       strategy);
  if (ZSTD_isError(strategy_result)) {
    ZSTD_freeCCtx(cctx);
    return 0;
  }

  ZSTD_inBuffer input = {nullptr, 0, 0};
  ZSTD_inBuffer output = {nullptr, 0, 0};

  std::string input_string = stream.ConsumeRemainingBytesAsString();
  input.src = reinterpret_cast<unsigned char*>(const_cast<char*>(input_string.c_str()));
  input.size = input_string.size();

  size_t const compress_result =
      ZSTD_compressStream(cctx, &output, &input);
  if (ZSTD_isError(compress_result)) {
    ZSTD_freeCCtx(cctx);
    return 0;
  }

  ZSTD_freeCCtx(cctx);
  return 0;
}