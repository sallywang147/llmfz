#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <cstring>
#include <string>

#include "mongoose.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  struct mg_mgr mgr;
  mg_mgr_init(&mgr);

  const std::string url = stream.ConsumeRemainingBytesAsString();
  const std::string func = stream.ConsumeRemainingBytesAsString();
  const std::string fnd = stream.ConsumeRemainingBytesAsString();

  mg_sntp_connect(&mgr, const_cast<char*>(url.c_str()),
                  const_cast<func_type*>(reinterpret_cast<const func_type*>(func.c_str())),
                  const_cast<char*>(fnd.c_str()));

  mg_mgr_free(&mgr);
  return 0;
}