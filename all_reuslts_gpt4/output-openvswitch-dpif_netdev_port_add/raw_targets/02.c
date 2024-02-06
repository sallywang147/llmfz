#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "dpif-netdev.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  struct dpif dpif_obj;
  struct netdev netdev_obj;
  int port_nop;

  // Consume data for dpif and netdev structs
  size_t consumed_dpif = stream.ConsumeData(&dpif_obj, sizeof(dpif_obj));
  size_t consumed_netdev = stream.ConsumeData(&netdev_obj, sizeof(netdev_obj));

  // If not enough data was available to consume, exit
  if (consumed_dpif < sizeof(dpif_obj) || consumed_netdev < sizeof(netdev_obj)) {
    return 0;
  }

  // Call the function under test
  dpif_netdev_port_add(&dpif_obj, &netdev_obj, &port_nop);

  return 0;
}