 #include <stddef.h>

#include "ares.h"

// Entrypoint for Clang's libfuzzer
int LLVMFuzzerTestOneInput(const unsigned char *data,
                           unsigned long size) {
  // Feed the data into each of the ares_parse_*_reply functions.
  struct ares_channeldata channel;
  char addr[128];
  int err;
  int flags = ARES_NI_NOFQDN | ARES_NI_NUMERICHOST;
  ares_getnameinfo(&channel, (struct sockaddr*)data, size, flags, NULL, addr);
  return 0;
}