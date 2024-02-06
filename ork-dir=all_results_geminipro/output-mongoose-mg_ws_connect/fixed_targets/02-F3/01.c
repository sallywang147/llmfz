#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstring>
#include <string>

extern "C" {
#include "mongoose.h"
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  struct mg_mgr mgr;
  mg_mgr_init(&mgr);
  const std::string url = stream.ConsumeRemainingBytesAsString();
  mg_ws_connect(&mgr, url.c_str(), nullptr, nullptr, nullptr);
  mg_mgr_free(&mgr);
  return 0;
}