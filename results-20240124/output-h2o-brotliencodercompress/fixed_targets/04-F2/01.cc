#include <brotli/encode.h>

extern "C" {
#include <brotli/decode.h>
}

int main() {
  BrotliEncoderCompress(nullptr, 0, nullptr, 0, nullptr);
  return 0;
}