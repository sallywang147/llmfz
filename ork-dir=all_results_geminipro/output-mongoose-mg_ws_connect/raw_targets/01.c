#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <string>

#include "mongoose.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  struct mg_mgr mgr;
  mg_mgr_init(&mgr);

  const std::string url = stream.ConsumeRemainingBytesAsString();
  const std::string fn_data = stream.ConsumeRemainingBytesAsString();
  const std::string fmt = stream.ConsumeRemainingBytesAsString();

  struct mg_connection *conn = mg_ws_connect(&mgr, const_cast<char*>(url.c_str()),
                                            nullptr, const_cast<char*>(fn_data.c_str()),
                                            const_cast<char*>(fmt.c_str()));
  mg_mgr_free(&mgr);
  return 0;
}