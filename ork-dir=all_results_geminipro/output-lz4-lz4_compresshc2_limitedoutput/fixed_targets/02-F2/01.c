#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <string>

extern "C" {
#include "lz4hc.h"
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  const size_t src_size = stream.ConsumeIntegralInRange<size_t>(0, 1 << 20);
  const size_t max_dst_size = stream.ConsumeIntegralInRange<size_t>(0, 1 << 20);
  const int c_level = stream.ConsumeIntegralInRange<int>(0, 16);
  std::vector<char> src_buffer(src_size);
  stream.ConsumeBytes<char>(src_buffer.data(), src_buffer.size());
  std::vector<char> dst_buffer(max_dst_size);

  const int ret = LZ4_compressHC2_limitedOutput(
      src_buffer.data(), dst_buffer.data(), src_buffer.size(), max_dst_size,
      c_level);
  return 0;
}