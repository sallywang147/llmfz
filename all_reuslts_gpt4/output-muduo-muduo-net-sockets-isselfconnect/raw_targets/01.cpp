#include <fuzzer/FuzzedDataProvider.h>
#include "muduo/net/sockets.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider stream(data, size);
  int sockfd = stream.ConsumeIntegral<int>();
  muduo::net::sockets::isSelfConnect(sockfd);
  return 0;
}