#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <string>

#include "mongoose.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  const std::string url = stream.ConsumeRemainingBytesAsString();
  const std::string func_name = stream.ConsumeRemainingBytesAsString();
  const std::string func_data = stream.ConsumeRemainingBytesAsString();

  struct mg_mgr mgr;
  mg_mgr_init(&mgr);

  struct mg_connection* conn = mg_sntp_connect(&mgr, const_cast<char*>(url.c_str()),
                                               nullptr, const_cast<char*>(func_data.c_str()));
  if (conn != nullptr) {
    mg_close_connection(conn);
  }

  mg_mgr_free(&mgr);
  return 0;
}