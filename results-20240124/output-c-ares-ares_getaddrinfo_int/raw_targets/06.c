 #include <stddef.h>

#include "ares.h"
#include "ares_private.h"

// Entrypoint for Clang's libfuzzer
int LLVMFuzzerTestOneInput(const unsigned char *data,
                           unsigned long size) {
  struct ares_channeldata channel;
  ares_init(&channel);
  ares_getaddrinfo_int(&channel, (char *)data, (char *)data, NULL, NULL, NULL);
  ares_destroy(&channel);
  return 0;
}