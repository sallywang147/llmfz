#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <vector>

#include "zdict.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  if (size < 2) {
    return 0;
  }

  FuzzedDataProvider stream(data, size);

  const size_t dictSize = stream.ConsumeIntegral<size_t>();
  std::vector<char> dictBuffer(dictSize);

  const size_t samplesSize = stream.ConsumeIntegral<size_t>();
  std::vector<char> samplesBuffer(samplesSize);

  std::vector<size_t> samplesSizes(samplesSize);
  for (size_t& sampleSize : samplesSizes) {
    sampleSize = stream.ConsumeIntegral<size_t>();
  }

  const int nbSamples = stream.ConsumeIntegral<int>();

  ZDICT_legacy_params_t params;
  params.dictID = stream.ConsumeIntegral<unsigned>();
  params.compressionLevel = stream.ConsumeIntegral<int>();

  ZDICT_trainFromBuffer_unsafe_legacy(dictBuffer.data(), dictSize, samplesBuffer.data(), samplesSizes.data(), nbSamples, &params);

  return 0;
}