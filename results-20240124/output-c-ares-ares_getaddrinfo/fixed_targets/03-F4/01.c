#include <stddef.h>
#include <ares.h>

extern "C" {
#include <ares_version.h>
#include <ares_nameser.h>
}

// Entrypoint for Clang's libfuzzer
int LLVMFuzzerTestOneInput(const unsigned char *data,
                           unsigned long size) {
  // Feed the data into ares_getaddrinfo.
  struct ares_channel channel;
  struct ares_addrinfo_hints hints;
  memset(&hints, 0, sizeof(hints));
  hints.ai_family = AF_INET;
  hints.ai_socktype = SOCK_STREAM;
  hints.ai_protocol = IPPROTO_TCP;
  hints.ai_flags = AI_PASSIVE;
  ares_getaddrinfo(&channel, NULL, NULL, &hints, NULL, NULL);
  ares_destroy(&channel);
  return 0;
}