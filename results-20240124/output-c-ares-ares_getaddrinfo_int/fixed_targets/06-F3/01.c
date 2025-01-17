#include <stddef.h>

extern "C" {
#include "ares.h"
#include "ares_private.h"
}

// Entrypoint for Clang's libfuzzer
int LLVMFuzzerTestOneInput(const unsigned char *data,
                           unsigned long size) {
  ares_channel channel;
  ares_init(&channel);
  ares_getaddrinfo(&channel, (char *)data, (char *)data, NULL, NULL, NULL);
  ares_destroy(&channel);
  return 0;
}