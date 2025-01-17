#include <fuzzer/FuzzedDataProvider.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>

#include "muduo/net/socketsOps.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
    FuzzedDataProvider stream(data, size);

    int sockfd = socket(AF_INET6, SOCK_STREAM, 0);
    if (sockfd < 0) {
        return 0;
    }

    struct sockaddr_in6 addr;
    addr.sin6_family = AF_INET6;
    addr.sin6_port = stream.ConsumeIntegral<uint16_t>();
    addr.sin6_flowinfo = stream.ConsumeIntegral<uint32_t>();
    addr.sin6_addr = in6addr_any;
    addr.sin6_scope_id = stream.ConsumeIntegral<uint32_t>();

    if (bind(sockfd, (struct sockaddr *)&addr, sizeof(addr)) < 0) {
        close(sockfd);
        return 0;
    }

    if (listen(sockfd, 1) < 0) {
        close(sockfd);
        return 0;
    }

    struct sockaddr_in6 peeraddr;
    muduo::net::sockets::accept(sockfd, &peeraddr);

    close(sockfd);
    return 0;
}