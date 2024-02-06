#include <cstdint>
#include <cstdlib>
#include <cstring>
#include <string>

#include "muduo/net/sockets.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  struct sockaddr_in6 addr;
  memset(&addr, 0, sizeof(addr));
  addr.sin6_family = AF_INET6;
  addr.sin6_port = htons(80);

  int fd = muduo::net::sockets::accept4(0, &addr, nullptr, SOCK_STREAM);
  if (fd >= 0) {
    close(fd);
  }
  return 0;
}