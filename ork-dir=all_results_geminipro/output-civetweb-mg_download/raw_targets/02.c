#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <string>

#include "mongoose.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  const std::string host = stream.ConsumeRemainingBytesAsString();
  const int port = stream.ConsumeIntegral<int>();
  const int use_ssl = stream.ConsumeBool();
  const size_t ebuf_len = stream.ConsumeIntegral<size_t>();
  char* ebuf = new char[ebuf_len];
  const std::string fmt = stream.ConsumeRemainingBytesAsString();

  struct mg_connection* conn = mg_download(
      const_cast<char*>(host.c_str()), port, use_ssl, ebuf, ebuf_len,
      const_cast<char*>(fmt.c_str()));
  if (conn != nullptr) {
    mg_close_connection(conn);
  }
  delete[] ebuf;
  return 0;
}