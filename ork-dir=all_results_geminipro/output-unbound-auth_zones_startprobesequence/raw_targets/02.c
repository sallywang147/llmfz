#include "config.h"
#include "auth.h"

int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  struct auth_zones *az = NULL;
  struct module_env *env = NULL;
  char *nm = NULL;
  size_t nmlen = 0;
  short dclass = 0;

  if (size > 0) {
    nm = (char *)malloc(size);
    memcpy(nm, data, size);
    nmlen = size;
  }

  auth_zones_startprobesequence(az, env, nm, nmlen, dclass);

  if (nm) {
    free(nm);
  }

  return 0;
}