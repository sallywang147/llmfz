#include <stddef.h>

#include "ares.h"

int LLVMFuzzerTestOneInput(const unsigned char *data, unsigned long size);

// Entrypoint for Clang's libfuzzer
int LLVMFuzzerTestOneInput(const unsigned char *data, unsigned long size) {
  // Feed the data into each of the ares_parse_*_reply functions.
  struct ares_channeldata channel;
  ares_init(&channel);
  struct ares_addrinfo_hints hints;
  memset(&hints, 0, sizeof(hints));

  ares_getaddrinfo_int(&channel, (char *)data, (char *)data, &hints, NULL, NULL);
  ares_destroy(&channel);

  return 0;
}