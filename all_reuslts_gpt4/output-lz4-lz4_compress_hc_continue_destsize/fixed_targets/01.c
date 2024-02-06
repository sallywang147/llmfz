#include <fuzzer/FuzzedDataProvider.h>
#include <cstddef>
#include <cstdint>
#include <cstring>
#include <vector>

#include "lz4.h"
#include "lz4hc.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  if (size < 4) {
    return 0;
  }
  
  FuzzedDataProvider stream(data, size);
  std::string src = stream.ConsumeRemainingBytesAsString();
  int srcSize = src.size();
  int targetDestSize = stream.ConsumeIntegral<int>();

  LZ4_streamHC_t* LZ4_streamHCPtr = LZ4_createStreamHC();
  if (LZ4_streamHCPtr == nullptr) {
    return 0;
  }

  std::vector<char> dst(targetDestSize);
  LZ4_compress_HC_continue_destSize(LZ4_streamHCPtr, src.data(), dst.data(), &srcSize, targetDestSize);

  LZ4_freeStreamHC(LZ4_streamHCPtr);
  return 0;
}