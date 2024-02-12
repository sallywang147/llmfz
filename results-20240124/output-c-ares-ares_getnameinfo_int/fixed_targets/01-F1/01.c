#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "ares.h"

extern "C" {
#include <ares.h>
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  static bool initialized = false;
  if (!initialized) {
    ares_library_init(ARES_LIB_INIT_ALL);
    initialized = true;
  }

  ares_channel channel;
  ares_channel_create(&channel, NULL, NULL);

  struct sockaddr_in addr;
  memset(&addr, 0, sizeof(addr));
  addr.sin_family = AF_INET;
  addr.sin_addr.s_addr = htonl(0x7F000001);
  addr.sin_port = htons(80);

  std::vector<uint8_t> output_buffer(1024);

  ares_getnameinfo(&channel, reinterpret_cast<struct sockaddr*>(&addr),
                       sizeof(addr), 0, NULL, output_buffer.data());

  ares_destroy(&channel);

  return 0;
}