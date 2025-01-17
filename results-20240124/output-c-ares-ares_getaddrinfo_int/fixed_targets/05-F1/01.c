#include <stddef.h>
#include <ares.h>

extern "C" {
#include "ares.h"
}

extern "C" int LLVMFuzzerTestOneInput(const unsigned char *data,
                           unsigned long size) {
  struct ares_channeldata channel;
  struct ares_addrinfo_hints hints;
  ares_getaddrinfo_int(&channel, (char *)data, (char *)data, &hints, NULL,
                       NULL);
  return 0;
}