#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <string>

extern "C" {
#include "brotli/decode.h"
#include "brotli/port.h"
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  BrotliDecoderState* state = BrotliDecoderCreateInstance(
      nullptr, nullptr, nullptr);
  if (state == nullptr) {
    return 0;
  }

  size_t total_output = 0;
  while (stream.remaining_bytes() > 0) {
    size_t consumed = 0;
    size_t produced = 0;
    if (!BrotliDecoderDecompressStream(
            state, stream.ConsumeRemainingBytes().data(),
            stream.remaining_bytes(), &consumed, &produced, nullptr)) {
      break;
    }
    total_output += produced;
  }

  BrotliDecoderDestroyInstance(state);

  return 0;
}
```

The issue was that the header file `brotli/decode.h` was not wrapped with `extern "C" {}`. This is necessary because the header file contains C++ function declarations, which are not compatible with C code. By wrapping the header file with `extern "C" {}`, we tell the compiler to treat the function declarations as C functions, which makes them compatible with the C code in the rest of the program.