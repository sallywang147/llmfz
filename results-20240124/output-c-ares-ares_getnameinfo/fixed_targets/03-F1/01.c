#include <stddef.h>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <sstream>
#include <string>
#include <vector>

#include "ares.h"

extern "C" {
#include <netdb.h>
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  // Create a channel
  ares_channel channel;
  int status = ares_init(&channel);
  if (status != ARES_SUCCESS) {
    fprintf(stderr, "Failed to initialize c-ares channel: %s\n",
            ares_strerror(status));
    return 0;
  }

  // Create a socket address
  struct sockaddr_in addr;
  memset(&addr, 0, sizeof(addr));
  addr.sin_family = AF_INET;
  addr.sin_port = htons(80);
  addr.sin_addr.s_addr = htonl(INADDR_LOOPBACK);

  // Create a buffer to store the name information
  char name[NI_MAXHOST];
  memset(name, 0, sizeof(name));

  // Call the function to be fuzzed
  ares_getnameinfo(channel, reinterpret_cast<struct sockaddr *>(&addr),
                   sizeof(addr), NI_NUMERICHOST, nullptr, name);

  // Destroy the channel
  ares_destroy(channel);

  return 0;
}