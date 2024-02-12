 #include <stddef.h>
#include <stdint.h>
#include <stdlib.h>

#include <brotli/decode.h>

// Entry point for LibFuzzer.
int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  if (size < 4)
    return 0;
  uint32_t dict_size = data[0] | (data[1] << 8) | (data[2] << 16) | (data[3] << 24);
  if (dict_size == 0)
    return 0;
  dict_size = (dict_size > size) ? size : dict_size;
  BrotliDecoderState* state = BrotliDecoderCreateInstance(0, 0, 0);
  if (!state) {
    // OOM is out-of-scope here.
    return 0;
  }
  BrotliDecoderAttachDictionary(state, 0, dict_size, (char*)data);
  BrotliDecoderDestroyInstance(state);
  return 0;
}