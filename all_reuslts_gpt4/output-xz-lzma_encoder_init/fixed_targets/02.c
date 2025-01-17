#include "fuzz_common.h"
#include "lzma.h"
#include <fuzzer/FuzzedDataProvider.h>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  if (size < 1) {
    return 0;
  }

  FuzzedDataProvider stream(data, size);

  // Initialize lzma_lz_encoder
  lzma_lz_encoder lz;
  lz.lz = NULL;
  lz.code = NULL;
  lz.end = NULL;

  // Initialize lzma_allocator
  lzma_allocator allocator;
  allocator.alloc = NULL;
  allocator.free = NULL;
  allocator.opaque = NULL;

  // Consume data for id
  size_t id = stream.ConsumeIntegral<size_t>();

  // Consume data for options
  std::string options = stream.ConsumeRandomLengthString();
  char *options_ptr = const_cast<char *>(options.c_str());

  // Initialize lzma_lz_options
  lzma_lz_options lz_options;
  lz_options.before_size = stream.ConsumeIntegral<uint32_t>();
  lz_options.dict_size = stream.ConsumeIntegral<uint32_t>();
  lz_options.after_size = stream.ConsumeIntegral<uint32_t>();
  lz_options.reserved1 = stream.ConsumeIntegral<uint32_t>();
  lz_options.reserved2 = stream.ConsumeIntegral<uint32_t>();
  lz_options.reserved3 = stream.ConsumeIntegral<uint32_t>();
  lz_options.reserved4 = stream.ConsumeIntegral<uint32_t>();

  // Call lzma_encoder_init
  lzma_encoder_init(&lz, &allocator, id, options_ptr, &lz_options);

  return 0;
}