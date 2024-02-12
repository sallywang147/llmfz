#include <ares.h>
#include <cstdint>
#include <cstring>
#include <cstdio>
#include <string>

extern "C" {
#include <ares.h>
}

static void ares_getnameinfo_int(ares_channeldata *channeldata,
                                 struct sockaddr *addr, int addrlen,
                                 int flags, func_type *callback,
                                 char *host) {
  // Do something
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  ares_getnameinfo_int(nullptr, nullptr, 0, 0, nullptr, nullptr);
  return 0;
}