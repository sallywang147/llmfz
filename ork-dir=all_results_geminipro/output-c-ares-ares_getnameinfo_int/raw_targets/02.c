#include <stddef.h>

#include "ares.h"

int LLVMFuzzerTestOneInput(const unsigned char *data, unsigned long size);

// Entrypoint for Clang's libfuzzer
int LLVMFuzzerTestOneInput(const unsigned char *data, unsigned long size) {
  // Feed the data into each of the ares_parse_*_reply functions.
  struct ares_channeldata channel;
  struct sockaddr_in addr;
  func_type func;
  char buf[1024];
  ares_getnameinfo_int(&channel, (struct sockaddr *)&addr, sizeof(addr), 0, &func, buf);
  return 0;
}