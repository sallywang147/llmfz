#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "LzmaEnc.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  // Prepare source buffer
  size_t srcLen = stream.ConsumeIntegralInRange<size_t>(0, size);
  std::vector<char> src = stream.ConsumeBytes<char>(srcLen);

  // Prepare destination buffer
  size_t destLen = srcLen + srcLen / 3 + 128;
  std::vector<char> dest(destLen);

  // Prepare properties
  CLzmaEncProps props;
  LzmaEncProps_Init(&props);
  props.level = stream.ConsumeIntegralInRange<int>(0, 9);
  props.dictSize = stream.ConsumeIntegralInRange<unsigned>(1 << 12, 1 << 27);
  props.lc = stream.ConsumeIntegralInRange<int>(0, 8);
  props.lp = stream.ConsumeIntegralInRange<int>(0, 4);
  props.pb = stream.ConsumeIntegralInRange<int>(0, 4);
  props.fb = stream.ConsumeIntegralInRange<int>(5, 273);
  props.numThreads = stream.ConsumeIntegralInRange<unsigned>(1, 2);

  // Prepare properties buffer
  size_t propsSize = LZMA_PROPS_SIZE;
  std::vector<char> propsEncoded(propsSize);

  // Prepare other parameters
  int writeEndMark = stream.ConsumeBool() ? 1 : 0;
  ICompressProgress progress = {0};
  ISzAlloc alloc = {0};
  ISzAlloc allocBig = {0};

  // Call the target function
  LzmaEncode(dest.data(), &destLen, src.data(), srcLen, &props, propsEncoded.data(), &propsSize, writeEndMark, &progress, &alloc, &allocBig);

  return 0;
}