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
  ares_channel channel;
  int status = ares_init(&channel);
  if (status != ARES_SUCCESS) {
    return 0;
  }
  ares_getaddrinfo(&channel, (char *)data, (char *)data, NULL, NULL, NULL);
  ares_destroy(&channel);
  return 0;
}