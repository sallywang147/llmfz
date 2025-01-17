#include <brotli/encode.h>

extern "C" {
#include <brotli/encode.h>
}

int main() {
  BrotliEncoderState* encoder = BrotliEncoderCreateInstance(0, 0, 0);
  BrotliEncoderSetParameter(encoder, BROTLI_PARAM_QUALITY, 11);
  BrotliEncoderCompressStream(encoder, BROTLI_OPERATION_FINISH, 0, 0, 0, 0, 0);
  BrotliEncoderDestroyInstance(encoder);
  return 0;
}