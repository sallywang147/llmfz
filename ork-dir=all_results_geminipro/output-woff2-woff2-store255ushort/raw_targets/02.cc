#include <string>
#include <woff2/decode.h>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t data_size) {
  size_t offset = 0;
  char dst[1024];
  woff2::Store255UShort(0, &offset, dst);
  return 0;
}