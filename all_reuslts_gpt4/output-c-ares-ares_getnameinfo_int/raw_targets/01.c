#include <stddef.h>
#include <stdint.h>
#include <netinet/in.h>

#include "ares.h"

typedef void (*func_type)(int, const char *, const char *, int, void *);

void callback(int status, const char *node, const char *service, int timeouts, void *arg) {
  // Do nothing
}

int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider stream(data, size);

  struct ares_channeldata channeldata;
  struct sockaddr_in addr;
  int flags = stream.ConsumeIntegral<int>();
  int family = stream.ConsumeIntegral<int>();
  func_type callback_func = &callback;
  char node[NI_MAXHOST];

  size_t consumed = stream.ConsumeData(&channeldata, sizeof(channeldata));
  if (consumed != sizeof(channeldata)) return 0;

  consumed = stream.ConsumeData(&addr, sizeof(addr));
  if (consumed != sizeof(addr)) return 0;

  ares_getnameinfo_int(&channeldata, (struct sockaddr*)&addr, flags, family, callback_func, node);

  return 0;
}