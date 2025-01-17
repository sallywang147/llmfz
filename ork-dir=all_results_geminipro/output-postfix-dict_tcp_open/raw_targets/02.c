#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <vector>

#include "dict.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider provider(data, size);

  int port = provider.ConsumeIntegralInRange<int>(0, 65535);
  int timeout = provider.ConsumeIntegralInRange<int>(0, 10000);

  std::string host = provider.ConsumeRandomLengthString(128);
  char* host_cstr = strdup(host.c_str());

  struct DICT* dict = dict_tcp_open(host_cstr, port, timeout);
  if (dict == nullptr) {
    free(host_cstr);
    return 0;
  }

  dict_close(dict);
  free(host_cstr);

  return 0;
}