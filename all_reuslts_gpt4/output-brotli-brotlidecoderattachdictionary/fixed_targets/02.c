#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>

#include <brotli/decode.h>
#include <fuzzer/FuzzedDataProvider.h>

// Entry point for LibFuzzer.
extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider stream(data, size);
  
  BrotliDecoderState *state = BrotliDecoderCreateInstance(0, 0, 0);
  if (!state) {
    // OOM is out-of-scope here.
    return 0;
  }

  int type = stream.ConsumeIntegral<int>();
  size_t dictionary_size = stream.ConsumeIntegral<size_t>();
  std::string dictionary_data = stream.ConsumeRemainingBytesAsString();
  
  BrotliDecoderAttachDictionary(state, type, dictionary_size, const_cast<char*>(dictionary_data.c_str()));

  BrotliDecoderDestroyInstance(state);
  return 0;
}