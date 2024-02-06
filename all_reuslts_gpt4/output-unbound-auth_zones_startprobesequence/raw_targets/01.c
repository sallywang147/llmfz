#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "auth_zones.h"
#include "module.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  // Define and initialize the parameters for auth_zones_startprobesequence
  struct auth_zones *az = (struct auth_zones *) malloc(sizeof(struct auth_zones));
  struct module_env *env = (struct module_env *) malloc(sizeof(struct module_env));
  size_t nmlen = stream.ConsumeIntegralInRange<size_t>(0, size);
  std::string nm = stream.ConsumeBytesAsString(nmlen);
  short dclass = stream.ConsumeIntegral<short>();

  // Call the function to fuzz
  int result = auth_zones_startprobesequence(az, env, nm.c_str(), nmlen, dclass);

  // Cleanup
  free(az);
  free(env);

  return 0;
}