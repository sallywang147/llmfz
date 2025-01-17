#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "zdict.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  // Define and initialize parameters for ZDICT_trainFromBuffer_unsafe_legacy
  size_t dictSize = 1024;
  std::vector<char> dictBuffer(dictSize);
  char* dict = dictBuffer.data();

  size_t samplesSizes = stream.ConsumeIntegralInRange<size_t>(0, size);
  std::vector<size_t> samplesSizesBuffer(samplesSizes);
  size_t* samplesSizesPtr = samplesSizesBuffer.data();

  int nbSamples = stream.ConsumeIntegral<int>();

  ZDICT_legacy_params_t params;
  params.dictID = stream.ConsumeIntegral<unsigned>();
  params.compressionLevel = stream.ConsumeIntegral<int>();
  params.notificationLevel = stream.ConsumeIntegral<int>();

  // Consume remaining bytes as samples
  std::vector<char> samplesBuffer = stream.ConsumeRemainingBytes<char>();
  char* samples = samplesBuffer.data();

  // Call ZDICT_trainFromBuffer_unsafe_legacy
  ZDICT_trainFromBuffer_unsafe_legacy(dict, dictSize, samples, samplesSizesPtr, nbSamples, &params);

  return 0;
}