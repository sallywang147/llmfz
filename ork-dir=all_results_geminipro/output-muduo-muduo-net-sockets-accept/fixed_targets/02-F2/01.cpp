#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include "muduo/net/sockets.h"

extern "C" {
#include <sys/socket.h>
#include <netinet/in.h>
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  char *new_str = (char *)malloc(size + 1);
  if (new_str == NULL) {
    return 0;
  }
  memcpy(new_str, data, size);
  new_str[size] = '\0';

  struct sockaddr_in6 addr;
  int fd = muduo::net::sockets::accept4(0, &addr, nullptr, SOCK_NONBLOCK | SOCK_CLOEXEC);
  if (fd > 0) {
    close(fd);
  }
  free(new_str);
  return 0;
}