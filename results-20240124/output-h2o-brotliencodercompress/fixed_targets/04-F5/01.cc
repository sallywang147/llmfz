#include <brotli/encode.h>

extern "C" {
#include <brotli/decode.h>
}

int main() {
  BrotliEncoderOperation op = BROTLI_OPERATION_PROCESS;
  BrotliEncoderCompressStream(nullptr, op, nullptr, 0, nullptr, nullptr, 0);
  return 0;
}