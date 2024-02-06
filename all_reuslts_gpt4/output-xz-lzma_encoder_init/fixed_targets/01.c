#include "fuzz_common.h"
#include "lzma.h"
#include <fuzzer/FuzzedDataProvider.h>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  if (size < 3) {
    return 0;
  }

  FuzzedDataProvider stream(data, size);

  // Initialize lzma_lz_encoder
  lzma_lz_encoder lz;
  memset(&lz, 0, sizeof(lzma_lz_encoder));

  // Initialize lzma_allocator
  lzma_allocator allocator;
  memset(&allocator, 0, sizeof(lzma_allocator));

  // Initialize lzma_lz_options
  lzma_lz_options lz_options;
  memset(&lz_options, 0, sizeof(lzma_lz_options));

  // Consume data for id
  size_t id = stream.ConsumeIntegral<size_t>();

  // Consume data for options
  std::string options = stream.ConsumeBytesAsString(1);
  
  // Call the function to fuzz
  lzma_encoder_init(&lz, &allocator, id, (char*)options.c_str(), &lz_options);

  return 0;
}