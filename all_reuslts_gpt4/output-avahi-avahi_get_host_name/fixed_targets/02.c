#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "avahi-common/strlst.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  const size_t ret_s_size = stream.ConsumeIntegralInRange<size_t>(0, 256);
  char* ret_s = new char[ret_s_size];

  avahi_get_host_name(ret_s, ret_s_size);

  delete[] ret_s;

  return 0;
}