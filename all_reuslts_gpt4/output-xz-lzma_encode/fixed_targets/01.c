#include <fuzzer/FuzzedDataProvider.h>
#include "lzma.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider stream(data, size);

  // Extract a string for the coder parameter
  std::string coder = stream.ConsumeRandomLengthString();
  char *coder_ptr = coder.c_str();

  // Initialize lzma_mf_s struct
  lzma_mf_s mf;
  mf.buffer = (uint8_t *)stream.ConsumeRemainingBytes().data();
  mf.size = stream.remaining_bytes();
  mf.read_pos = stream.ConsumeIntegralInRange<size_t>(0, mf.size);
  mf.write_pos = stream.ConsumeIntegralInRange<size_t>(mf.read_pos, mf.size);
  mf.read_ahead = stream.ConsumeIntegralInRange<size_t>(0, mf.size - mf.read_pos);
  mf.offset = stream.ConsumeIntegralInRange<uint32_t>(0, UINT32_MAX);
  mf.read_limit = stream.ConsumeIntegralInRange<size_t>(0, mf.size);

  // Initialize out parameters
  std::string out = stream.ConsumeRandomLengthString();
  size_t out_size = out.size();
  size_t out_pos = stream.ConsumeIntegralInRange<size_t>(0, out_size);

  // Call the function to fuzz
  lzma_encode(coder_ptr, &mf, out.data(), &out_pos, out_size);

  return 0;
}