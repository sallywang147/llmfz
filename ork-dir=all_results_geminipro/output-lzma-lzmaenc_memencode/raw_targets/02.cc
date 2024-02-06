#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <string>
#include <vector>

#include "7z.h"
#include "7zAlloc.h"
#include "7zCrc.h"
#include "7zFile.h"
#include "CpuArch.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  const size_t srcLen = stream.ConsumeIntegral<size_t>();
  std::vector<char> src(srcLen);
  stream.ConsumeBytes(src.data(), srcLen);

  const size_t destLen = stream.ConsumeIntegral<size_t>();
  std::vector<char> dest(destLen);

  const int writeEndMark = stream.ConsumeBool() ? 1 : 0;

  ISzAlloc alloc = {SzAlloc, SzFree};
  ISzAlloc allocBig = {SzAlloc, SzFree};
  ICompressProgress progress = {0};

  int result = LzmaEnc_MemEncode(nullptr, dest.data(), &destLen, src.data(), srcLen,
                                 writeEndMark, &progress, &alloc, &allocBig);
  if (result != SZ_OK) {
    return 0;
  }

  return 0;
}