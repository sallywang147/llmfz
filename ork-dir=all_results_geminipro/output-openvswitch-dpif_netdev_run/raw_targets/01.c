#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <cstring>
#include <string>

#include "dpif.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  const size_t dpif_size = stream.ConsumeIntegralInRange<size_t>(
      sizeof(struct dpif), sizeof(struct dpif) * 2);
  struct dpif* dpif = reinterpret_cast<struct dpif*>(std::malloc(dpif_size));
  if (dpif == nullptr) {
    return 0;
  }
  memset(dpif, 0, dpif_size);

  dpif->netdev_run = dpif_netdev_run;

  dpif_netdev_run(dpif);

  std::free(dpif);
  return 0;
}