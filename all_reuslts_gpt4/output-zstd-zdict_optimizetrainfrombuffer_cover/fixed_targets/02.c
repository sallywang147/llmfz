#include <fuzzer/FuzzedDataProvider.h>
#include <cstddef>
#include <cstdint>
#include <vector>
#include "zdict.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  const size_t dictBufferCapacity = 128 KB;
  char dictBuffer[dictBufferCapacity];
  size_t dictSize = dictBufferCapacity;
  std::vector<char> samplesBuffer = stream.ConsumeRemainingBytes<char>();
  size_t samplesSizes = samplesBuffer.size();
  int nbThreads = stream.ConsumeIntegral<int>();
  ZDICT_cover_params_t params;
  params.k = stream.ConsumeIntegral<unsigned>();
  params.d = stream.ConsumeIntegral<unsigned>();
  params.steps = stream.ConsumeIntegral<unsigned>();
  params.nbThreads = nbThreads;
  params.zParams.compressionLevel = stream.ConsumeIntegral<int>();
  params.zParams.notificationLevel = stream.ConsumeIntegral<int>();
  params.zParams.dictID = stream.ConsumeIntegral<unsigned>();
  size_t ret = ZDICT_optimizeTrainFromBuffer_cover(dictBuffer, dictSize, samplesBuffer.data(), &samplesSizes, 1, &params);
  return 0;
}