#include <fuzzer/FuzzedDataProvider.h>

#include <algorithm>
#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <string>

extern "C" {
#include "zstd.h"
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  const size_t input_size = stream.ConsumeIntegralInRange<size_t>(0, 10000);
  const size_t output_size = stream.ConsumeIntegralInRange<size_t>(0, 10000);
  ZSTD_CCtx* compressor = ZSTD_createCCtx();
  if (compressor == nullptr) {
    return 0;
  }

  std::string input_string = stream.ConsumeRemainingBytesAsString();
  std::string output_string(output_size, '\0');

  size_t compressed_size = ZSTD_compress2(compressor, (void*)output_string.data(),
                                          output_size, (void*)input_string.data(),
                                          input_size);
  ZSTD_freeCCtx(compressor);
  return 0;
}