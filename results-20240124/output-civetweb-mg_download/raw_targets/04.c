 #include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include "civetweb.h"

#include <fuzzer/FuzzedDataProvider.h>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  const char* host = stream.ConsumeRandomLengthString();
  const int port = stream.ConsumeIntegralInRange<int>(1, 65535);
  const int use_ssl = stream.ConsumeBool();
  const char* ebuf = stream.ConsumeRandomLengthString();
  const size_t ebuf_len = stream.ConsumeIntegralInRange<size_t>(1, 1024);
  const char* fmt = stream.ConsumeRandomLengthString();
  mg_download((char*)host, port, use_ssl, (char*)ebuf, ebuf_len, (char*)fmt);
  return 0;
}