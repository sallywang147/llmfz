#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <cstring>
#include <string>

#include <fuzzer/FuzzedDataProvider.h>

extern "C" {
#include "dpif.h"
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  const size_t name_len = stream.ConsumeIntegralInRange<size_t>(0, 64);
  char* name = static_cast<char*>(malloc(name_len + 1));
  stream.ConsumeBytes(name, name_len);
  name[name_len] = '\0';

  dp_netdev* dp = nullptr;
  const int ret = create_dp_netdev(name, nullptr, &dp);
  if (ret != 0) {
    free(name);
    return 0;
  }
  free(name);
  dpif_destroy_dp_netdev(dp);
  return 0;
}