#include "auth_zones.h"
#include "module_env.h"
#include "util/data/dname.h"
#include <fuzzer/FuzzedDataProvider.h>

extern "C" {
#include <stdlib.h>
}

int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider stream(data, size);

  struct auth_zones az;
  struct module_env env;
  char *nm = stream.ConsumeBytesAsString(stream.ConsumeIntegralInRange(0, size));
  size_t nmlen = stream.ConsumeIntegralInRange(0, size);
  short dclass = stream.ConsumeIntegral<short>();

  auth_zones_init(&az, &env, NULL);
  int ret = auth_zones_startprobesequence(&az, &env, nm, nmlen, dclass);
  auth_zones_cleanup(&az, &env);
  free(nm);

  return ret;
}