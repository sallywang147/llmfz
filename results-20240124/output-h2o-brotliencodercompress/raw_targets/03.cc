 #include <stddef.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include "brotli/encode.h"
#include "brotli/types.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  if (size < 1 || size > 1000000) {
    return 0;
  }

  BrotliEncoderState* state = BrotliEncoderCreateInstance(0, 0, 0);
  if (state == NULL) {
    return 0;
  }

  BrotliEncoderSetParameter(state, BROTLI_PARAM_QUALITY, 11);
  BrotliEncoderSetParameter(state, BROTLI_PARAM_LGWIN, 24);

  size_t available_in = size;
  const uint8_t* next_in = data;
  size_t available_out = 1000000;
  uint8_t* next_out = (uint8_t*)malloc(available_out);
  if (next_out == NULL) {
    BrotliEncoderDestroyInstance(state);
    return 0;
  }

  BrotliEncoderCompressStream(state, BROTLI_OPERATION_FINISH, &available_in,
                             &next_in, &available_out, &next_out, NULL);

  BrotliEncoderDestroyInstance(state);
  free(next_out);

  return 0;
}