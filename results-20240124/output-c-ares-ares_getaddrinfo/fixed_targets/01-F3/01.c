#include <stddef.h>

#include "ares.h"

extern "C" {
#include "ares_setup.h"
}

// Entrypoint for Clang's libfuzzer
extern "C" int LLVMFuzzerTestOneInput(const unsigned char *data,
                                     unsigned long size) {
  // Feed the data into ares_getaddrinfo.
  struct ares_channeldata channel;
  int status = ares_init(&channel);
  if (status != ARES_SUCCESS) {
    return 0;
  }
  ares_getaddrinfo(&channel, NULL, NULL, NULL, NULL, NULL);
  ares_destroy(&channel);

  return 0;
}