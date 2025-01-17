#include <stddef.h>
#include <arpa/inet.h>

#include "ares.h"

extern "C" {
#include "ares_nameser.h"
}

int LLVMFuzzerTestOneInput(const unsigned char *data, unsigned size) {
  struct sockaddr_in addr;
  memset(&addr, 0, sizeof(addr));
  addr.sin_family = AF_INET;
  addr.sin_addr.s_addr = inet_addr("127.0.0.1");
  ares_getnameinfo_int(NULL, (struct sockaddr *)&addr, sizeof(addr),
                       ARES_NI_NUMERICHOST, NULL, NULL);
  return 0;
}