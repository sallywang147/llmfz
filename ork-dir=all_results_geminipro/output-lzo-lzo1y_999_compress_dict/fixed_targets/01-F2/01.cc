#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <vector>

extern "C" {
#include "lzo/lzoconf.h"
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  const size_t input_size = stream.ConsumeIntegralInRange<size_t>(1, 10000);
  const size_t output_size = stream.ConsumeIntegralInRange<size_t>(1, 10000);
  const size_t dict_size = stream.ConsumeIntegralInRange<size_t>(1, 10000);

  std::vector<uint8_t> input_buffer(input_size);
  stream.ConsumeBytes<uint8_t>(input_buffer.data(), input_size);
  std::vector<uint8_t> output_buffer(output_size);
  std::vector<uint8_t> dict_buffer(dict_size);
  stream.ConsumeBytes<uint8_t>(dict_buffer.data(), dict_size);

  size_t output_len = output_size;
  int ret = lzo1y_999_compress_dict(
      reinterpret_cast<char*>(input_buffer.data()), input_size,
      reinterpret_cast<char*>(output_buffer.data()), &output_len,
      nullptr, reinterpret_cast<char*>(dict_buffer.data()), dict_size);

  return 0;
}