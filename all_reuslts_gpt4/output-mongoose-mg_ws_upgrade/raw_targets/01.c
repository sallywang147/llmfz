#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "mongoose.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  struct mg_connection c;
  struct mg_http_message hm;
  std::string fmt = stream.ConsumeRandomLengthString();
  
  mg_ws_upgrade(&c, &hm, fmt.c_str());

  return 0;
}