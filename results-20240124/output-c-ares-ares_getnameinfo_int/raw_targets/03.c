 #include <stddef.h>

#include "ares.h"

// Entrypoint for Clang's libfuzzer
int LLVMFuzzerTestOneInput(const unsigned char *data,
                           unsigned long size) {
  // Feed the data into each of the ares_parse_*_reply functions.
  struct ares_channeldata channel;
  memset(&channel, 0, sizeof(channel));

  struct sockaddr_in addr;
  memset(&addr, 0, sizeof(addr));
  addr.sin_family = AF_INET;
  addr.sin_port = 12345;
  addr.sin_addr.s_addr = 0x10203040;

  struct sockaddr_in6 addr6;
  memset(&addr6, 0, sizeof(addr6));
  addr6.sin6_family = AF_INET6;
  addr6.sin6_port = 12345;
  addr6.sin6_addr.s6_addr[0] = 0x10;
  addr6.sin6_addr.s6_addr[1] = 0x20;
  addr6.sin6_addr.s6_addr[2] = 0x30;
  addr6.sin6_addr.s6_addr[3] = 0x40;

  ares_getnameinfo_int(&channel, reinterpret_cast<struct sockaddr*>(&addr),
                        sizeof(addr), NI_NUMERICHOST, NULL, NULL);
  ares_getnameinfo_int(&channel, reinterpret_cast<struct sockaddr*>(&addr6),
                        sizeof(addr6), NI_NUMERICHOST, NULL, NULL);

  return 0;
}