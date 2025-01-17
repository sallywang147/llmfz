#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "auth_zones.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  struct auth_zones az;
  struct module_env env;
  short dclass = stream.ConsumeIntegral<short>();
  struct sockaddr_storage addr;
  int addrlen = sizeof(struct sockaddr_storage);
  int has_serial = stream.ConsumeBool();
  int serial = stream.ConsumeIntegral<int>();
  int refused;

  // Consume a string for the 'nm' parameter
  std::string nm = stream.ConsumeRandomLengthString();
  size_t nmlen = nm.size();

  // Call the target function
  auth_zones_notify(&az, &env, nm.c_str(), nmlen, dclass, &addr, addrlen, has_serial, serial, &refused);

  return 0;
}