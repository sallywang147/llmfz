#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <cstring>
#include <string>

#include <fuzzer/FuzzedDataProvider.h>

#include "dpif.h"

extern "C" {
int create_dp_netdev(const char* name, const struct dpif_dp_netdev_ops* ops,
                     struct dp_netdev** dp);
void dpif_destroy_dp_netdev(struct dp_netdev* dp);
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
  dpif_destroy_dp_netdev(dp);
  free(name);
  return 0;
}