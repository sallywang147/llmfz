#include <stddef.h>
#include <ares.h>

extern "C" {
#include <arpa/inet.h>
#include <netdb.h>
}

int LLVMFuzzerTestOneInput(const unsigned char *data, unsigned long size);

int LLVMFuzzerTestOneInput(const unsigned char *data, unsigned long size) {
  struct ares_channeldata channel;
  struct sockaddr_in addr;
  int errcode;
  char host[NI_MAXHOST];
  func_type callback = [](void *arg, int status, int timeouts,
                          unsigned char *abuf, int alen) {};
  ares_init(&channel);
  ares_getnameinfo(&channel, reinterpret_cast<struct sockaddr *>(&addr),
                   sizeof(addr), NI_NUMERICHOST, callback, host);
  ares_destroy(&channel);
  return 0;
}