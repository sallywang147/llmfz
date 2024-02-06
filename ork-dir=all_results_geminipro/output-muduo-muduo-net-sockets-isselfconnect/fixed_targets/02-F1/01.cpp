#include <stdint.h>
#include <stdlib.h>

extern "C" {
#include "muduo/net/sockets.h"
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  int fd = *(int *)data;
  muduo::net::sockets::isSelfConnect(fd);
  return 0;
}