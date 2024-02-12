 #include <stddef.h>

#include "ares.h"

// Entrypoint for Clang's libfuzzer
int LLVMFuzzerTestOneInput(const unsigned char *data,
                           unsigned long size) {
  struct ares_channeldata channel;
  struct ares_addrinfo_hints hints;
  hints.ai_flags = ARES_AI_CANONNAME;
  hints.ai_family = AF_UNSPEC;
  hints.ai_socktype = SOCK_STREAM;
  hints.ai_protocol = IPPROTO_TCP;
  hints.ai_addr = nullptr;
  hints.ai_canonname = nullptr;
  hints.ai_next = nullptr;

  ares_getaddrinfo_int(&channel, "example.com", "80", &hints, nullptr, nullptr);

  return 0;
}