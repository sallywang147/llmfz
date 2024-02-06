#include <fuzzer/FuzzedDataProvider.h>
#include <cstddef>
#include <cstdint>
#include <lzo/lzo1z.h>

// The size of the working memory required by the compressor.
#define LZO1Z_999_MEM_COMPRESS  (LZO1Z_MEM_COMPRESS + (5 * 16384L * sizeof(lzo_bytep)))

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  if (size < 1) {
    return 0;
  }

  FuzzedDataProvider stream(data, size);

  // Initialize the LZO library
  if (lzo_init() != LZO_E_OK) {
    return 0;
  }

  // Create and initialize the necessary buffers and sizes
  size_t in_len = stream.remaining_bytes() / 2;
  size_t out_len = in_len + in_len / 16 + 64 + 3;  // As recommended in LZO examples
  size_t dict_len = stream.remaining_bytes() - in_len;

  char* in = (char*)stream.ConsumeBytes<uint8_t>(in_len).data();
  char* out = new char[out_len];
  char* wrkmem = new char[LZO1Z_999_MEM_COMPRESS];
  char* dict = (char*)stream.ConsumeRemainingBytes().data();

  // Compress the input data
  lzo1z_999_compress_dict(in, in_len, out, &out_len, wrkmem, dict, dict_len);

  // Clean up
  delete[] out;
  delete[] wrkmem;

  return 0;
}