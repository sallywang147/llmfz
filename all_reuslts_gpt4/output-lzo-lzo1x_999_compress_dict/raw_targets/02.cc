#include <fuzzer/FuzzedDataProvider.h>
#include <lzo/lzo1x.h>

#include <cstddef>
#include <cstdint>
#include <vector>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  // Initialize the LZO library
  if (lzo_init() != LZO_E_OK) {
    return 0;
  }

  FuzzedDataProvider stream(data, size);

  // Divide the data into three parts: input, output and dictionary.
  const size_t in_len = stream.ConsumeIntegralInRange<size_t>(0, size / 3);
  std::string in = stream.ConsumeBytesAsString(in_len);

  const size_t out_len = stream.ConsumeIntegralInRange<size_t>(0, (size - in_len) / 2);
  std::string out(out_len, '\0');

  const size_t dict_len = size - in_len - out_len;
  std::string dict = stream.ConsumeRemainingBytesAsString();

  // Allocate memory for the working memory required by the function.
  std::vector<char> wrkmem(LZO1X_999_MEM_COMPRESS);

  // Call the function to fuzz
  size_t out_len_actual = out_len;
  lzo1x_999_compress_dict(const_cast<char*>(in.data()), in_len, const_cast<char*>(out.data()), &out_len_actual, wrkmem.data(), const_cast<char*>(dict.data()), dict_len);

  return 0;
}