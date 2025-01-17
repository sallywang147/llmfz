#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>

#include "dpif.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  struct dpif dpif;
  dpif_netdev_init(&dpif, nullptr);
  dpif_netdev_run(&dpif);
  dpif_netdev_deinit(&dpif, true);
  return 0;
}