#include <stdint.h>
#include <stdlib.h>

extern "C" {
#include "muduo/net/sockets.h"
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  if (size < sizeof(int)) {
    return 0;
  }
  int fd = *(int *)data;
  if (muduo::net::sockets::isSelfConnect(fd)) {
    return 0;
  }
  return 0;
}