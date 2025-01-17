#include <stddef.h>
#include <ares.h>

extern "C" {
#include "ares_setup.h"
#include <time.h>
#include <sys/time.h>
}

// Entrypoint for Clang's libfuzzer
int LLVMFuzzerTestOneInput(const unsigned char *data,
                           unsigned long size) {
  // Feed the data into ares_getaddrinfo_int
  struct ares_channeldata channel;
  char *node = NULL;
  char *service = NULL;
  struct ares_addrinfo_hints hints;
  ares_callback callback = NULL;
  char *arg = NULL;

  ares_getaddrinfo_int(&channel, node, service, &hints, callback, arg);

  return 0;
}