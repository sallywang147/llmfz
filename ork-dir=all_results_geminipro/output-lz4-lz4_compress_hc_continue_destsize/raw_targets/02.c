#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <cstring>
#include <vector>

#include "lz4hc.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  LZ4_streamHC_t* LZ4_streamHCPtr = LZ4_createStreamHC();
  if (LZ4_streamHCPtr == nullptr) {
    return 0;
  }

  const size_t src_size = stream.ConsumeIntegralInRange<size_t>(0, 1024);
  std::vector<char> src(src_size);
  stream.ConsumeBytes<char>(src.data(), src_size);

  const size_t target_dest_size =
      stream.ConsumeIntegralInRange<size_t>(0, 1024);
  std::vector<char> dst(target_dest_size);

  int src_size_ptr = src_size;
  const int ret = LZ4_compress_HC_continue_destSize(
      LZ4_streamHCPtr, src.data(), dst.data(), &src_size_ptr, target_dest_size);
  if (ret != 0) {
    return 0;
  }

  LZ4_freeStreamHC(LZ4_streamHCPtr);
  return 0;
}