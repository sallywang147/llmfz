#include <stddef.h>
#include <ares.h>

extern "C" {
#include "ares.h"
}

// Entrypoint for Clang's libfuzzer
extern "C" int LLVMFuzzerTestOneInput(const unsigned char *data,
                                    unsigned long size) {
  // Feed the data into each of the ares_parse_*_reply functions.
  ares_channel channel;
  struct sockaddr_in sin;
  struct sockaddr_in6 sin6;
  struct sockaddr *sa = (struct sockaddr *)&sin;
  int salen = sizeof(sin);
  bool type = ares_getnameinfo;
  char addr[16];
  ares_getnameinfo_int(&channel, sa, salen, AF_INET, &type, addr);

  sa = (struct sockaddr *)&sin6;
  salen = sizeof(sin6);
  ares_getnameinfo_int(&channel, sa, salen, AF_INET6, &type, addr);

  return 0;
}