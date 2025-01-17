#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "dpif-netdev.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  
  struct dpif_3273 dpif_class;
  struct dpif_3187 *dpif_ptr = nullptr;
  
  // Consume data for 'name' parameter
  std::string name = stream.ConsumeRandomLengthString();
  
  // Consume data for 'create' parameter
  bool create = stream.ConsumeBool();
  
  // Call the target function
  int ret = dpif_netdev_open(&dpif_class, const_cast<char*>(name.c_str()), create, &dpif_ptr);
  
  // Clean up
  if (dpif_ptr) {
    dpif_close(dpif_ptr);
  }
  
  return 0;
}