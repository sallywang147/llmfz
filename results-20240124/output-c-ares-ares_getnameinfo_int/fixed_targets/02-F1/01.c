#include <stddef.h>

#include "ares.h"

// Entrypoint for Clang's libfuzzer
extern "C" int LLVMFuzzerTestOneInput(const unsigned char *data,
                           unsigned long size) {
  // Feed the data into ares_getnameinfo_int.
  struct ares_channeldata channel;
  struct sockaddr addr;
  int addrlen = sizeof(addr);
  int flags = 0;
  ares_callback callback = NULL;
  char host[NI_MAXHOST];
  ares_getnameinfo_int(&channel, &addr, addrlen, flags, callback, host);
  return 0;
}