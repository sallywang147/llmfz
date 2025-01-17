#include <stddef.h>
#include <string.h> // for memset

#include "ares.h"

// Entrypoint for Clang's libfuzzer
extern "C" int LLVMFuzzerTestOneInput(const unsigned char *data,
                           unsigned long size) {
  // Feed the data into each of the ares_parse_*_reply functions.
  struct ares_channeldata channel;
  ares_init(&channel);

  struct ares_addrinfo_hints hints;
  memset(&hints, 0, sizeof(hints));

  ares_getaddrinfo(&channel, "www.example.com", "80", &hints, NULL, NULL);

  ares_destroy(&channel);
  return 0;
}