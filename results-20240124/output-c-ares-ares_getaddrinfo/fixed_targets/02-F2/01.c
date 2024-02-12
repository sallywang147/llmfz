#include <stddef.h>
#include <ares.h>

extern "C" {
#include "ares_version.h"
#include "ares.h"
}

// Entrypoint for Clang's libfuzzer
int LLVMFuzzerTestOneInput(const unsigned char *data,
                           unsigned long size) {
  // Feed the data into ares_getaddrinfo.
  ares_channel channel;
  ares_channel_init(&channel, ARES_OPT_FLAGS, ARES_FLAG_NOCHECKRESP, NULL);

  ares_getaddrinfo(&channel, (char *)data, (char *)data, NULL, NULL, NULL);

  ares_channel_destroy(&channel);
  return 0;
}