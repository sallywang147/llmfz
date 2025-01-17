#include <stddef.h>

#include "ares.h"

int LLVMFuzzerTestOneInput(const unsigned char *data, unsigned long size);

// Entrypoint for Clang's libfuzzer
int LLVMFuzzerTestOneInput(const unsigned char *data, unsigned long size) {
  // Feed the data into ares_getnameinfo_int.
  struct ares_channeldata channel;
  struct sockaddr_in addr;
  int errcode = 0;
  func_type callback = NULL;
  char addrstr[1024];
  ares_getnameinfo_int(&channel, (struct sockaddr *)&addr, sizeof(addr),
                       ARES_NI_NUMERICHOST, callback, addrstr);
  return 0;
}