#include <fuzzer/FuzzedDataProvider.h>
#include "auth_zones.h"
#include "module_env.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider stream(data, size);

  // Initialize the auth_zones and module_env structures
  struct auth_zones az;
  struct module_env env;

  // Consume data for the name
  std::string name = stream.ConsumeRandomLengthString();
  char *nm = const_cast<char*>(name.c_str());
  size_t nmlen = name.size();

  // Consume data for the class
  short dclass = stream.ConsumeIntegral<short>();

  // Call the function to fuzz
  auth_zones_startprobesequence(&az, &env, nm, nmlen, dclass);

  return 0;
}