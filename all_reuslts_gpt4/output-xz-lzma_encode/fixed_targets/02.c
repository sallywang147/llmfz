#include <fuzzer/FuzzedDataProvider.h>
#include "lzma.h"
#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider stream(data, size);

  // Extract coder from the input
  std::string coder = stream.ConsumeRandomLengthString();
  if (coder.empty()) {
    return 0;
  }

  // Initialize lzma_mf_s struct
  lzma_mf_s mf;
  mf.buffer_size = stream.ConsumeIntegral<uint32_t>();
  mf.read_pos = stream.ConsumeIntegral<uint32_t>();
  mf.read_limit = stream.ConsumeIntegral<uint32_t>();
  mf.write_pos = stream.ConsumeIntegral<uint32_t>();
  mf.pending = stream.ConsumeIntegral<uint32_t>();
  mf.read_ahead = stream.ConsumeIntegral<uint32_t>();
  mf.nice_len = stream.ConsumeIntegral<uint32_t>();
  mf.depth = stream.ConsumeIntegral<uint32_t>();
  mf.offset = stream.ConsumeIntegral<uint32_t>();
  mf.find = NULL;

  // Prepare output buffer
  size_t out_size = stream.remaining_bytes();
  char *out = (char*)malloc(out_size);
  if (!out) {
    return 0;
  }

  size_t out_pos = 0;

  // Call the function to fuzz
  lzma_encode(coder.data(), &mf, out, &out_pos, out_size);

  free(out);
  return 0;
}