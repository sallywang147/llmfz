#include <stddef.h>
#include <ares.h>

extern "C" {
#include "ares_setup.h"
#include <sys/time.h>
#include <time.h>
}

// Entrypoint for Clang's libfuzzer
int LLVMFuzzerTestOneInput(const unsigned char *data,
                           unsigned long size) {
  // Feed the data into ares_getaddrinfo.
  struct ares_channeldata channel;
  ares_init(&channel);
  ares_getaddrinfo(&channel, (char *)data, (char *)data, NULL, NULL, NULL);
  ares_destroy(&channel);
  return 0;
}