#include <cstdint>
#include <cstdlib>
#include <cstring>
#include <string>

extern "C" {
#include <sys/socket.h>
#include <netinet/in.h>
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  struct sockaddr_in6 addr;
  memset(&addr, 0, sizeof(addr));
  addr.sin6_family = AF_INET6;
  addr.sin6_port = htons(80);

  // Fix the issue by replacing `muduo::net::sockets::accept4` with `::accept4`.
  int fd = ::accept4(0, &addr, nullptr, SOCK_STREAM);
  if (fd >= 0) {
    close(fd);
  }
  return 0;
}