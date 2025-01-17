#include <fuzzer/FuzzedDataProvider.h>
#include <cstddef>
#include <cstdint>
#include <vector>
#include "snappy.h"
#include "snappy-sinksource.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  
  const size_t compressed_length = stream.ConsumeIntegralInRange<size_t>(0, size);
  std::string compressed = stream.ConsumeBytesAsString(compressed_length);
  char* compressed_ptr = const_cast<char*>(compressed.data());
  
  const size_t iov_cnt = stream.ConsumeIntegral<size_t>();
  std::vector<snappy::SnappySinkAllocator::Datablock> iov(iov_cnt);
  
  for(size_t i = 0; i < iov_cnt; ++i) {
    const size_t block_size = stream.ConsumeIntegralInRange<size_t>(0, size);
    std::string block_data = stream.ConsumeBytesAsString(block_size);
    iov[i].data = const_cast<char*>(block_data.data());
    iov[i].size = block_size;
  }

  snappy::RawUncompressToIOVec(compressed_ptr, compressed_length, iov.data(), iov_cnt);

  return 0;
}