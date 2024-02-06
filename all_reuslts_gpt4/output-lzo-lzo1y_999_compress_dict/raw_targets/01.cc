#include <fuzzer/FuzzedDataProvider.h>
#include <lzo/lzo1y.h>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  if (size < 2)
    return 0;

  FuzzedDataProvider stream(data, size);

  std::string in = stream.ConsumeBytesAsString(stream.remaining_bytes() / 2);
  std::string dict = stream.ConsumeRemainingBytesAsString();

  size_t out_len = in.size() + in.size() / 16 + 64 + 3;
  char* out = new char[out_len];

  char wrkmem[LZO1Y_999_MEM_COMPRESS];

  lzo1y_999_compress_dict(in.data(), in.size(), out, &out_len, wrkmem, dict.data(), dict.size());

  delete[] out;

  return 0;
}