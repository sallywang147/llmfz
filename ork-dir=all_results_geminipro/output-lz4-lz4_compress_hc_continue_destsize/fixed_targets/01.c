#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <string>
#include <vector>

extern "C" {
#include "lz4hc.h"
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  const int src_size = stream.ConsumeIntegralInRange<int>(0, 1024 * 1024);
  const int target_dest_size =
      stream.ConsumeIntegralInRange<int>(0, 1024 * 1024);
  std::vector<char> src_data(src_size);
  stream.ConsumeBytes<char>(src_data.data(), src_size);

  std::vector<char> dst_data(target_dest_size);

  LZ4_streamHC_u stream_state;
  LZ4_resetStreamHC(&stream_state, 1);
  const int result = LZ4_compress_HC_continue_destSize(
      &stream_state, src_data.data(), dst_data.data(), src_size,
      target_dest_size);
  if (result < 0) {
    return 0;
  }

  return 0;
}