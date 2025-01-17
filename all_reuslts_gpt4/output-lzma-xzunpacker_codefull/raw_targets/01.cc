#include <fuzzer/FuzzedDataProvider.h>
#include <cstddef>
#include <cstdint>
#include <vector>

#include "XzUnpacker.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  CXzUnpacker xzUnpacker;
  XzUnpacker_Construct(&xzUnpacker);

  std::vector<char> dest(4096);
  size_t destLen = dest.size();

  std::vector<char> src = stream.ConsumeRemainingBytes<char>();
  size_t srcLen = src.size();

  int status;
  int finishMode = stream.ConsumeBool() ? LZMA_FINISH_ANY : LZMA_FINISH_END;

  XzUnpacker_CodeFull(&xzUnpacker, dest.data(), &destLen, src.data(), &srcLen, finishMode, &status);

  XzUnpacker_Free(&xzUnpacker);

  return 0;
}