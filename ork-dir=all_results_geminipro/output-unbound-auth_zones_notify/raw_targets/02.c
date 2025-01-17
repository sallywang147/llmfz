#include "config.h"
#include "auth/auth.h"
#include "sldns/sbuffer.h"
#include "util/data/dname.h"
#include "util/data/packed_rrset.h"
#include "util/module.h"
#include "util/net_help.h"
#include "util/random.h"
#include "util/regional.h"
#include "util/config_file.h"
#include "util/data/msgreply.h"

int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  struct auth_zones az;
  struct module_env env;
  char *nm;
  size_t nmlen;
  short dclass;
  struct sockaddr_storage addr;
  int addrlen;
  int has_serial;
  int serial;
  int *refused;

  if (size < 12) return 0;
  nm = (char*)data;
  nmlen = data[0];
  dclass = data[1] | (data[2] << 8);
  addrlen = data[3] | (data[4] << 8);
  has_serial = data[5];
  serial = data[6] | (data[7] << 8) | (data[8] << 16) | (data[9] << 24);
  refused = (int*)(data + 10);
  data += 11;
  size -= 11;
  if (nmlen > 255 || addrlen > sizeof(addr)) return 0;
  if (size < nmlen + addrlen) return 0;
  memcpy(addr.ss_data, data, addrlen);
  data += addrlen;
  size -= addrlen;
  if (size < nmlen) return 0;
  memcpy(nm, data, nmlen);
  data += nmlen;
  size -= nmlen;

  auth_zones_init(&az);
  auth_zones_notify(&az, &env, nm, nmlen, dclass, &addr, addrlen, has_serial, serial, refused);
  auth_zones_deinit(&az, &env);

  return 0;
}