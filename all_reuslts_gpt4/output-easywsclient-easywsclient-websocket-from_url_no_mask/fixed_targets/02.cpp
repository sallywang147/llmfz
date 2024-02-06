#include <stddef.h>
#include <stdint.h>
#include <string.h>

#include "easywsclient.hpp"
#include <fuzzer/FuzzedDataProvider.h>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider fuzzedDataProvider(data, size);
  std::string url = fuzzedDataProvider.ConsumeRandomLengthString();
  std::string origin = fuzzedDataProvider.ConsumeRemainingBytesAsString();
  easywsclient::WebSocket::from_url_no_mask(&url, &origin);
  return 0;
}