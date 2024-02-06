#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "dpif-netdev.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  // Extract a string for name parameter
  std::string name = stream.ConsumeRandomLengthString();
  char *name_ptr = const_cast<char*>(name.c_str());

  // Create a struct dpif_3273 object
  struct dpif_3273 dpif_class;
  dpif_class.param1 = stream.ConsumeIntegral<int>();
  dpif_class.param2 = stream.ConsumeIntegral<int>();
  dpif_class.param3 = stream.ConsumeIntegral<int>();

  // Create a pointer to struct dp_netdev
  struct dp_netdev *dp_netdev_ptr = nullptr;

  // Call the target function
  int result = create_dp_netdev(name_ptr, &dpif_class, &dp_netdev_ptr);

  // Free the created dp_netdev if it was successfully created
  if (result == 0 && dp_netdev_ptr != nullptr) {
    destroy_dp_netdev(dp_netdev_ptr);
  }

  return 0;
}