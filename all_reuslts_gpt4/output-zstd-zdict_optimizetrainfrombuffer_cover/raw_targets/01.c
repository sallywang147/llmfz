#include <fuzzer/FuzzedDataProvider.h>
#include <cstddef>
#include <cstdint>
#include <vector>
#include "zdict.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  if (size < 4) {
    return 0;
  }

  FuzzedDataProvider stream(data, size);
  
  const size_t dict_size = stream.ConsumeIntegralInRange<size_t>(1, size / 2);
  std::vector<char> dict(dict_size);

  const size_t samples_size = size - dict_size;
  std::vector<char> samples(samples_size);
  std::vector<size_t> samples_sizes(1, samples_size);

  ZDICT_cover_params_t params;
  params.k = stream.ConsumeIntegral<uint32_t>();
  params.d = stream.ConsumeIntegral<uint32_t>();
  params.steps = stream.ConsumeIntegral<uint32_t>();
  params.nbThreads = stream.ConsumeIntegral<uint32_t>();
  params.zParams.compressionLevel = stream.ConsumeIntegral<int>();

  ZDICT_optimizeTrainFromBuffer_cover(dict.data(), dict_size, samples.data(), samples_sizes.data(), 1, &params);

  return 0;
}