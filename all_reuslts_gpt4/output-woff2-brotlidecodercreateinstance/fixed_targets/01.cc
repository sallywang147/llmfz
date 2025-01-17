#include <fuzzer/FuzzedDataProvider.h>
#include <brotli/decode.h>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider stream(data, size);

  // We need to provide three parameters to BrotliDecoderCreateInstance.
  // The first two parameters are function pointers for allocation and deallocation.
  // We will use the default malloc and free functions.
  // The third parameter is a pointer to a memory manager. We will pass NULL since we're using the default memory manager.

  BrotliDecoderState* s = BrotliDecoderCreateInstance(malloc, free, nullptr);
  if (s == nullptr) {
    return 0;
  }

  // Since we have created a new BrotliDecoderState instance, we must ensure to free it when we're done.
  BrotliDecoderDestroyInstance(s);

  return 0;
}