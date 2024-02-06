#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <string>

extern "C" {
#include "mongoose.h"
}

int mg_sntp_connect(struct mg_mgr*, const char*, const char*, const char*);

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  const std::string url = stream.ConsumeRemainingBytesAsString();
  const std::string func_name = stream.ConsumeRemainingBytesAsString();
  const std::string func_data = stream.ConsumeRemainingBytesAsString();

  struct mg_mgr mgr;
  mg_mgr_init(&mgr);

  struct mg_connection* conn = mg_sntp_connect(&mgr, url.c_str(),
                                               nullptr, func_data.c_str());
  if (conn != nullptr) {
    mg_close_connection(conn);
  }

  mg_mgr_free(&mgr);
  return 0;
}