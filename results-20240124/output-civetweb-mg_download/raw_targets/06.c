 #include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "civetweb.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  static bool initialized = false;
  if (!initialized) {
    mg_init_library(0);
    initialized = true;
  }
  FuzzedDataProvider stream(data, size);
  int port = stream.ConsumeIntegral<int>();
  const char* host = stream.ConsumeRandomLengthString();
  int use_ssl = stream.ConsumeBool();
  char ebuf[256];
  char fmt[256];
  mg_download((char*)host, port, use_ssl, ebuf, sizeof(ebuf), fmt);
  return 0;
}