 #include <stddef.h>

#include "ares.h"

// Entrypoint for Clang's libfuzzer
int LLVMFuzzerTestOneInput(const unsigned char *data,
                           unsigned long size) {
  // Feed the data into each of the ares_parse_*_reply functions.
  struct ares_channeldata channel;
  struct sockaddr_in addr;
  int len = sizeof(addr);
  func_type callback = NULL;
  ares_getnameinfo_int(&channel, (struct sockaddr*)&addr, len, AF_INET,
                       callback, NULL);

  return 0;
}