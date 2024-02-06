#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <vector>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  // Allocate input buffer.
  const size_t in_len = stream.ConsumeIntegralInRange<size_t>(0, 1024);
  std::vector<char> in(in_len);
  stream.ConsumeBytes(in.data(), in_len);

  // Allocate output buffer.
  size_t out_len = 0;
  std::vector<char> out(in_len * 2);

  // Allocate working memory buffer.
  char wrkmem[LZO1Z_999_MEM_COMPRESS];

  // Allocate dictionary buffer.
  const size_t dict_len = stream.ConsumeIntegralInRange<size_t>(0, 1024);
  std::vector<char> dict(dict_len);
  stream.ConsumeBytes(dict.data(), dict_len);

  // Call the function.
  int ret = lzo1z_999_compress_dict(in.data(), in_len, out.data(), &out_len,
                                    wrkmem, dict.data(), dict_len);
  if (ret != LZO_E_OK) {
    return 0;
  }

  return 0;
}