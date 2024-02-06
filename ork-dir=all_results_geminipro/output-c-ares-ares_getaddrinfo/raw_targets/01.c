#include <stddef.h>

#include "ares.h"

int LLVMFuzzerTestOneInput(const unsigned char *data, unsigned long size);

// Entrypoint for Clang's libfuzzer
int LLVMFuzzerTestOneInput(const unsigned char *data, unsigned long size) {
  // Feed the data into each of the ares_parse_*_reply functions.
  struct ares_channeldata *channel = NULL;
  int status = ares_init(&channel);
  if (status != ARES_SUCCESS) {
    return 0;
  }

  struct ares_addrinfo_hints hints;
  memset(&hints, 0, sizeof(hints));
  hints.ai_family = AF_INET;
  hints.ai_socktype = SOCK_STREAM;

  ares_getaddrinfo(channel, "example.com", NULL, &hints, NULL, NULL);

  ares_destroy(channel);

  return 0;
}