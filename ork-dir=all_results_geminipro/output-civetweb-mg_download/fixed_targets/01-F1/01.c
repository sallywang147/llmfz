#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <string>

#include "mongoose.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  const std::string host = stream.ConsumeRemainingBytesAsString();
  const int port = stream.ConsumeIntegral<int>();
  const int use_ssl = stream.ConsumeBool();
  const size_t ebuf_len = stream.ConsumeIntegralInRange<size_t>(0, 1024);
  char* ebuf = static_cast<char*>(std::malloc(ebuf_len));
  const std::string fmt = stream.ConsumeRemainingBytesAsString();

  struct mg_connection* conn = mg_download(host.c_str(), port,
                                          use_ssl, ebuf, ebuf_len,
                                          fmt.c_str());
  mg_close_connection(conn);
  std::free(ebuf);
  return 0;
}