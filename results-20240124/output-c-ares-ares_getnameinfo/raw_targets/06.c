 #include <stddef.h>

#include "ares.h"

extern "C" int LLVMFuzzerTestOneInput(const unsigned char *data,
                           unsigned long size) {
  // Feed the data into each of the ares_parse_*_reply functions.
  struct ares_channeldata channel;
  struct sockaddr_in addr;
  int addrlen = sizeof(addr);
  int flags = ARES_NI_NOFQDN;
  func_type callback = NULL;
  char buf[1024];
  ares_getnameinfo(&channel, reinterpret_cast<struct sockaddr*>(&addr), addrlen,
                   flags, callback, buf);
  return 0;
}