#include <cstddef>
#include <cstdint>
#include <string>

extern "C" {
#include <woff2/decode.h>
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t data_size) {
  size_t offset = 0;
  std::string dst(std::min(woff2::ComputeWOFF2FinalSize(data, data_size), woff2::kDefaultMaxSize), 0);
  woff2::Store255UShort(data_size, &offset, dst.data());
  return 0;
}