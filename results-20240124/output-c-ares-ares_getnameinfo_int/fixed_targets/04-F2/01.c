#include <stddef.h>
#include <ares.h>

// Entrypoint for Clang's libfuzzer
int LLVMFuzzerTestOneInput(const unsigned char *data,
                           unsigned long size) {
  // Feed the data into ares_getnameinfo_int.
  extern "C" {
    struct ares_channeldata channel;
    int ares_getnameinfo_int(ares_channeldata *, struct sockaddr *, int, int, char *, char *);
  }
  struct sockaddr_in addr;
  addr.sin_family = AF_INET;
  addr.sin_port = 0;
  addr.sin_addr.s_addr = 0;

  ares_getnameinfo_int(&channel, (struct sockaddr *)&addr, sizeof(addr),
                      ARES_NI_NUMERICHOST, NULL, NULL);

  return 0;
}