#include <stddef.h>
#include <stdint.h>
#include <string.h>

#include "easywsclient.hpp"
#include <fuzzer/FuzzedDataProvider.h>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  std::string str(reinterpret_cast<const char *>(data), size);
  easywsclient::WebSocket::from_url_no_mask(str);
  return 0;
}