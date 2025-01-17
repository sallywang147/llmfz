#include <fuzzer/FuzzedDataProvider.h>
#include <lzo/lzo1x.h>
#include <cstdint>
#include <cstddef>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  if (size < 1) {
    return 0;
  }

  FuzzedDataProvider fuzzed_data(data, size);

  // Split the data into two parts: one for input and one for dictionary
  const size_t in_len = fuzzed_data.ConsumeIntegralInRange<size_t>(0, size);
  std::string in = fuzzed_data.ConsumeBytesAsString(in_len);
  std::string dict = fuzzed_data.ConsumeRemainingBytesAsString();

  // Prepare output buffer and working memory
  char out[LZO1X_999_MEM_COMPRESS];
  size_t out_len = sizeof(out);
  char wrkmem[LZO1X_999_MEM_COMPRESS];

  // Call the target function
  lzo1x_999_compress_dict(const_cast<char*>(in.data()), in.size(),
                          out, &out_len, wrkmem,
                          const_cast<char*>(dict.data()), dict.size());

  return 0;
}