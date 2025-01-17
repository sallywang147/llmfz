#include <stddef.h>

#include "ares.h"

extern "C" {
#include <ares_version.h>
#include <ares_private.h>
}

// Entrypoint for Clang's libfuzzer
int LLVMFuzzerTestOneInput(const unsigned char *data,
                           unsigned long size) {
  // Feed the data into ares_getnameinfo
  struct ares_channeldata channel;
  ares_channel_init(&channel, ARES_OPT_FLAGS, 0, 0, NULL, NULL);
  struct sockaddr_in addr;
  addr.sin_family = AF_INET;
  addr.sin_port = 0;
  addr.sin_addr.s_addr = 0;
  ares_getnameinfo(&channel, (struct sockaddr*)&addr, sizeof(addr),
                   ARES_NI_NUMERICHOST, NULL, NULL);
  ares_channel_destroy(&channel);
  return 0;
}