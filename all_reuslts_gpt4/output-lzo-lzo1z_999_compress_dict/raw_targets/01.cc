#include <fuzzer/FuzzedDataProvider.h>
#include <lzo/lzo1z.h>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  if (size < 2) {
    return 0;
  }

  FuzzedDataProvider stream(data, size);

  // Split the input data into two parts. First part is used as the input to compress,
  // and the second part is used as the dictionary.
  const size_t in_len = stream.ConsumeIntegralInRange<size_t>(1, size - 1);
  std::string in = stream.ConsumeBytesAsString(in_len);
  std::string dict = stream.ConsumeRemainingBytesAsString();

  char out[LZO1Z_999_MEM_COMPRESS];
  size_t out_len = LZO1Z_999_MEM_COMPRESS;

  char wrkmem[LZO1Z_999_MEM_COMPRESS];

  lzo1z_999_compress_dict(in.data(), in_len, out, &out_len, wrkmem, dict.data(), dict.size());

  return 0;
}