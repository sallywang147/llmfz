#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>

#include "dpif.h"

extern "C" {
#include "dpif-netdev.h"
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  struct dpif *dpif = nullptr;
  struct netdev *netdev = nullptr;
  int port_no = 0;
  dpif_netdev_port_add(dpif, netdev, &port_no);
  return 0;
}