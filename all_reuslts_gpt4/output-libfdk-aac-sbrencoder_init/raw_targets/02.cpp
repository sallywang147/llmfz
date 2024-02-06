#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>

#include "sbr_encoder.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  int noElements = stream.ConsumeIntegral<int>();
  int inputBufferBufSize = stream.ConsumeIntegral<int>();
  int syntaxFlags = stream.ConsumeIntegral<int>();
  int aot = stream.ConsumeIntegral<int>();
  int transformFactor = stream.ConsumeIntegral<int>();
  int headerPeriod = stream.ConsumeIntegral<int>();
  int statesInitFlag = stream.ConsumeIntegral<int>();

  std::vector<short> inputBuffer = stream.ConsumeBytes<short>(inputBufferBufSize);
  int coreBandwidth = stream.ConsumeIntegral<int>();
  int inputBufferOffset = stream.ConsumeIntegral<int>();
  int numChannels = stream.ConsumeIntegral<int>();
  int coreSampleRate = stream.ConsumeIntegral<int>();
  int downSampleFactor = stream.ConsumeIntegral<int>();
  int frameLength = stream.ConsumeIntegral<int>();
  int delay = stream.ConsumeIntegral<int>();

  SBR_ENCODER hSbrEncoder;
  SBR_ELEMENT_INFO elInfo;

  sbrEncoder_Init(&hSbrEncoder, &elInfo, noElements, inputBuffer.data(), inputBufferBufSize, &coreBandwidth, &inputBufferOffset, &numChannels, syntaxFlags, &coreSampleRate, &downSampleFactor, &frameLength, aot, &delay, transformFactor, headerPeriod, statesInitFlag);

  return 0;
}