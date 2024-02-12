#include <brotli/encode.h>

extern "C" {
#include <brotli/encode.h>
}

int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  // ...
  int quality = 11;
  int lgwin = 22;
  size_t compressed_size = 0;
  char *compressed_buffer = new char[size];
  BrotliEncoderCompress(quality, lgwin, 0, size, (char *)data, &compressed_size, compressed_buffer);
  // ...
}