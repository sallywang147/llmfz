#include <fuzzer/FuzzedDataProvider.h>

extern "C" {
#include <brotli/decode.h>
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider stream(data, size);

  BrotliDecoderState *s = BrotliDecoderCreateInstance(nullptr, nullptr, nullptr);
  if (s == nullptr) return 0;

  int ret;
  size_t available_in = stream.remaining_bytes();
  const uint8_t *next_in = stream.ConsumeBytes<uint8_t>(available_in).data();
  size_t total_out = 0;
  while (available_in > 0) {
    ret = BrotliDecoderDecompressStream(s, &available_in, &next_in, &total_out,
                                       nullptr, nullptr);
    if (ret != BROTLI_DECODER_RESULT_NEEDS_MORE_INPUT) break;
    available_in = stream.remaining_bytes();
    next_in = stream.ConsumeBytes<uint8_t>(available_in).data();
  }

  // Call BrotliDecoderTakeOutput to consume the decompressed data.
  char *output = BrotliDecoderTakeOutput(s, &total_out);
  if (output != nullptr) {
    free(output);
  }

  BrotliDecoderDestroyInstance(s);

  return 0;
}
```

The complete fixed code is shown above. The only change is that the `#include <brotli/decode.h>` line is wrapped with `extern "C" {}`. This tells the compiler to treat the included header file as a C header file, which prevents name mangling of the function names.