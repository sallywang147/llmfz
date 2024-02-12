 #include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <string>

#include "zstd.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  const size_t src_size = stream.ConsumeIntegral<size_t>();
  const size_t dst_size = stream.ConsumeIntegral<size_t>();
  const std::string src_str = stream.ConsumeRemainingBytesAsString();
  char* src = const_cast<char*>(src_str.c_str());
  char* dst = new char[dst_size];

  size_t compressed_size = ZSTD_compress2(nullptr, dst, dst_size, src, src_size);
  delete[] dst;
  return 0;
}