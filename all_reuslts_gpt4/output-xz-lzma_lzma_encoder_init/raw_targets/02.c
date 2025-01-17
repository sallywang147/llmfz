#include <fuzzer/FuzzedDataProvider.h>
#include "lzma.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider stream(data, size);

  // Consume data for lzma_next_coder_s
  lzma_next_coder_s next;
  next.id = stream.ConsumeIntegral<lzma_vli>();
  next.init = NULL;
  next.code = NULL;
  next.end = NULL;
  next.get_check = NULL;
  next.update = NULL;
  next.coder = NULL;
  next.buffer.alloc = NULL;
  next.buffer.pos = 0;
  next.buffer.size = 0;

  // Consume data for lzma_allocator
  lzma_allocator allocator;
  allocator.alloc = NULL;
  allocator.free = NULL;
  allocator.opaque = NULL;

  // Consume data for lzma_filter_info_s
  lzma_filter_info_s filters;
  filters.id = stream.ConsumeIntegral<lzma_vli>();
  filters.options = NULL;
  filters.encoder = NULL;
  filters.decoder = NULL;
  filters.init = NULL;
  filters.id_chain = NULL;
  filters.next = NULL;

  // Call the function to fuzz
  int result = lzma_lzma_encoder_init(&next, &allocator, &filters);

  return 0;
}