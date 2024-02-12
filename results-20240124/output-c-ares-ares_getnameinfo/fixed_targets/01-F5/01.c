#include <stddef.h>
#include <c-ares/ares.h>

extern "C" {
#include <c-ares/ares_nameser.h>
}

// Entrypoint for Clang's libfuzzer
int LLVMFuzzerTestOneInput(const unsigned char *data,
                           unsigned long size) {
  // Feed the data into each of the ares_parse_*_reply functions.
  ares_channel channel;
  struct sockaddr_in addr;
  addr.sin_family = AF_INET;
  addr.sin_port = htons(53);
  addr.sin_addr.s_addr = htonl(0x01020304);
  ares_getnameinfo(&channel, (struct sockaddr *) &addr, sizeof(addr),
                   ARES_NI_NUMERICHOST, NULL, NULL);

  return 0;
}