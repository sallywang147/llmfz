#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <cstring>
#include <string>

#include "mongoose.h"

extern "C" {
#include "mongoose.h"
}

typedef void (*func_type)(struct mg_connection *, const char *, char *);

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  struct mg_mgr mgr;
  mg_mgr_init(&mgr);

  const std::string url = stream.ConsumeRemainingBytesAsString();
  const std::string func = stream.ConsumeRemainingBytesAsString();
  const std::string fnd = stream.ConsumeRemainingBytesAsString();

  mg_sntp_connect(&mgr, url.c_str(),
                  reinterpret_cast<func_type>(func.c_str()),
                  fnd.c_str());

  mg_mgr_free(&mgr);
  return 0;
}