#include <fuzzer/FuzzedDataProvider.h>
#include <lzo1x.h>

#include <cstddef>
#include <cstdint>
#include <cstring>
#include <vector>

extern "C" {
#include <lzo1x.h>
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  const std::vector<uint8_t> input = stream.ConsumeBytes<uint8_t>(stream.ConsumeIntegralInRange<size_t>(0, size));
  const std::vector<uint8_t> dictionary = stream.ConsumeBytes<uint8_t>(stream.ConsumeIntegralInRange<size_t>(0, size));
  const size_t input_size = input.size();
  const size_t dictionary_size = dictionary.size();
  std::vector<uint8_t> output(input_size);

  size_t output_size = output.size();
  std::vector<uint8_t> work_mem(input_size);
  int result = lzo1x_999_compress_dict(reinterpret_cast<char*>(input.data()), input_size,
                                      reinterpret_cast<char*>(output.data()), &output_size,
                                      reinterpret_cast<char*>(work_mem.data()),
                                      reinterpret_cast<char*>(dictionary.data()), dictionary_size);
  if (result != LZO_E_OK) {
    return 0;
  }

  output.resize(output_size);
  return 0;
}