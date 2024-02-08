#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>

#include <brotli/decode.h>

// Entry point for LibFuzzer.
int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  BrotliDecoderState *state = BrotliDecoderCreateInstance(0, 0, 0);
  if (!state) {
    // OOM is out-of-scope here.
    return 0;
  }

  FuzzedDataProvider stream(data, size);
  int dictionary_id = stream.ConsumeIntegral<int>();
  size_t dictionary_size = stream.ConsumeIntegral<size_t>();
  std::vector<uint8_t> dictionary = stream.ConsumeBytes<uint8_t>(dictionary_size);

  BrotliDecoderAttachDictionary(state, dictionary_id, dictionary_size, dictionary.data());

  BrotliDecoderDestroyInstance(state);
  return 0;
}