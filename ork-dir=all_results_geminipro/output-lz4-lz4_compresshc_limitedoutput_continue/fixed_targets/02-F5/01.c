#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <string>

#include "lz4.h"
#include "lz4hc.h"

extern "C" {
int LZ4_compressHC_limitedOutput_continue(LZ4_streamHC_u* ctx, const char* src,
                                          char* dst, int srcSize, int maxDstSize);
int LZ4_resetStreamHC(LZ4_streamHC_u* ctx, int srcSize);
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  const int max_dst_size = stream.ConsumeIntegral<int>();
  const int src_size = stream.ConsumeIntegral<int>();
  const std::string input = stream.ConsumeRemainingBytesAsString();

  char* dst = new char[max_dst_size];
  char* src = new char[src_size];
  memcpy(src, input.c_str(), src_size);

  LZ4_streamHC_u ctx;
  LZ4_resetStreamHC(&ctx, src_size);

  int result = LZ4_compressHC_limitedOutput_continue(&ctx, src, dst, src_size,
                                                    max_dst_size);

  delete[] dst;
  delete[] src;

  return 0;
}
```

The corrected code includes the `lz4hc.h` header file, which contains the definitions of the `LZ4_compressHC_limitedOutput_continue` and `LZ4_resetStreamHC` functions. This fixes the build error and allows the code to compile successfully.