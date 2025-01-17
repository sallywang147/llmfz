#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include "muduo/net/sockets.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  if (size < sizeof(struct sockaddr_in6)) {
    return 0;
  }

  int sockfd = socket(AF_INET6, SOCK_STREAM, 0);
  if (sockfd < 0) {
    return 0;
  }

  struct sockaddr_in6 addr;
  memcpy(&addr, data, sizeof(struct sockaddr_in6));
  addr.sin6_family = AF_INET6;

  bind(sockfd, (struct sockaddr *)&addr, sizeof(struct sockaddr_in6));

  listen(sockfd, 5);

  struct sockaddr_in6 client_addr;
  muduo::net::sockets::accept(sockfd, &client_addr);

  close(sockfd);
  
  return 0;
}