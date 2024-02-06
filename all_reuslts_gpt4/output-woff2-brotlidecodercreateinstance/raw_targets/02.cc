#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include <brotli/decode.h>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  if (size < 1) {
    return 0;
  }

  char* alloc_ptr = (char*)malloc(size);
  if (alloc_ptr == NULL) {
    return 0;
  }
  memcpy(alloc_ptr, data, size);

  BrotliDecoderState* s = BrotliDecoderCreateInstance(0, 0, alloc_ptr);
  if (s == NULL) {
    free(alloc_ptr);
    return 0;
  }

  BrotliDecoderDestroyInstance(s);
  free(alloc_ptr);
  return 0;
}