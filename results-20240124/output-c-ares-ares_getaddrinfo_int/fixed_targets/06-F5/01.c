#include <stddef.h>

extern "C" {
#include "ares.h"
#include "ares_private.h"
}

// Entrypoint for Clang's libfuzzer
int LLVMFuzzerTestOneInput(const unsigned char *data,
                           unsigned long size) {
  ares_channel channel;
  int status = ares_init(&channel);
  if (status != ARES_SUCCESS) {
    return 0;
  }
  ares_getaddrinfo(&channel, (char *)data, (char *)data, NULL, NULL, NULL);
  ares_destroy(&channel);
  return 0;
}