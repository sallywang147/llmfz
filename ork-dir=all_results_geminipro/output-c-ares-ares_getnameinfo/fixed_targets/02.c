#include <stddef.h>

#include "ares.h"

int LLVMFuzzerTestOneInput(const unsigned char *data, unsigned long size);

// Entrypoint for Clang's libfuzzer
int LLVMFuzzerTestOneInput(const unsigned char *data, unsigned long size) {
  // Feed the data into each of the ares_parse_*_reply functions.
  struct ares_channeldata channel;
  struct sockaddr_in addr;
  int errcode = 0;
  int socktype = 0;
  func_type callback;
  char buf[1024];
  ares_getnameinfo(&channel, (struct sockaddr *)&addr, sizeof(addr), socktype, &callback, buf);
  return 0;
}