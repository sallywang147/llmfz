#include <brotli/encode.h>

extern "C" {
#include <brotli/decode.h>
}

int main() {
  BrotliEncoderCompressStream(nullptr, 0, nullptr, 0, nullptr, nullptr);
  return 0;
}