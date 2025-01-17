#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "dpif-netdev.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  // Extract a string for the name parameter.
  std::string name = stream.ConsumeRandomLengthString();
  
  // Create and initialize a dpif_3273 struct for the class parameter.
  struct dpif_3273 class_instance;
  class_instance.param1 = stream.ConsumeIntegral<int>();
  class_instance.param2 = stream.ConsumeIntegral<int>();
  class_instance.param3 = stream.ConsumeIntegral<int>();
  
  // Create a pointer to a dp_netdev struct for the dpp parameter.
  struct dp_netdev* dpp = nullptr;

  // Call the target function.
  create_dp_netdev(const_cast<char*>(name.c_str()), &class_instance, &dpp);

  return 0;
}