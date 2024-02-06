#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

extern "C" char* decode_tiles_row_wise_mt(struct VP9Decoder*, char*, char*);

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  struct VP9Decoder* decoder = new VP9Decoder();

  FuzzedDataProvider provider(data, size);

  size_t first_buffer_size = provider.ConsumeIntegralInRange<size_t>(0, 1<<20);
  std::vector<uint8_t> first_buffer(first_buffer_size);
  provider.ConsumeBytes<uint8_t>(first_buffer.data(), first_buffer_size);

  size_t second_buffer_size = provider.ConsumeIntegralInRange<size_t>(0, 1<<20);
  std::vector<uint8_t> second_buffer(second_buffer_size);
  provider.ConsumeBytes<uint8_t>(second_buffer.data(), second_buffer_size);

  char* result = decode_tiles_row_wise_mt(decoder, reinterpret_cast<char*>(first_buffer.data()), reinterpret_cast<char*>(second_buffer.data()));

  delete decoder;

  return 0;
}