#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <vector>

#include "7z.h"

extern "C" SRes LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  const size_t srcLen = stream.ConsumeIntegralInRange<size_t>(0, 10000);
  std::vector<char> src(srcLen);
  stream.ConsumeBytes<char>(src.data(), srcLen);

  const size_t destLen = stream.ConsumeIntegralInRange<size_t>(0, 10000);
  std::vector<char> dest(destLen);
  size_t destLenActual = destLen;

  const int writeEndMark = stream.ConsumeBool();

  ISzAlloc alloc = {nullptr, nullptr};
  ISzAlloc allocBig = {nullptr, nullptr};
  ICompressProgress progress = {nullptr, nullptr};

  SRes ret = LzmaEnc_MemEncode(nullptr, dest.data(), &destLenActual,
                                    src.data(), srcLen, writeEndMark, &progress,
                                    &alloc, &allocBig);
  if (ret != SZ_OK) {
    return 0;
  }

  return 0;
}