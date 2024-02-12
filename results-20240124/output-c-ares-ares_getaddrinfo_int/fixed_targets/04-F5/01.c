#include <stddef.h>

#include "ares.h"

// Entrypoint for Clang's libfuzzer
extern "C" int LLVMFuzzerTestOneInput(const unsigned char *data,
                           unsigned long size) {
  // Feed the data into each of the ares_parse_*_reply functions.
  ares_channel channel;
  int status = ares_init(&channel);
  if (status != ARES_SUCCESS) {
    return 0;
  }
  struct ares_addrinfo_hints hints;
  hints.ai_flags = ARES_AI_CANONNAME;
  hints.ai_family = AF_UNSPEC;
  hints.ai_socktype = SOCK_STREAM;
  hints.ai_protocol = IPPROTO_TCP;
  ares_getaddrinfo_int(&channel, NULL, NULL, &hints, NULL, NULL);
  ares_destroy(&channel);
  return 0;
}