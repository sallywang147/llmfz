#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "mongoose.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  std::string host = stream.ConsumeRandomLengthString();
  int port = stream.ConsumeIntegral<int>();
  int use_ssl = stream.ConsumeBool();
  std::string ebuf = stream.ConsumeRandomLengthString();
  std::string fmt = stream.ConsumeRandomLengthString();

  struct mg_connection* conn = mg_download(const_cast<char*>(host.c_str()), port, use_ssl, const_cast<char*>(ebuf.c_str()), ebuf.size(), const_cast<char*>(fmt.c_str()));

  if (conn != nullptr) {
    mg_close_connection(conn);
  }

  return 0;
}