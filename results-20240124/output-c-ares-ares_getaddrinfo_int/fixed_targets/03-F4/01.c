#include <stddef.h>

#include "ares.h"

extern "C" {
#include <ares.h>
}

typedef struct ares_channeldata ares_channel;

// Entrypoint for Clang's libfuzzer
extern "C" int LLVMFuzzerTestOneInput(const unsigned char *data,
                                      unsigned long size) {
  struct ares_channel *channel;
  struct ares_addrinfo_hints hints;
  int status;

  status = ares_library_init(ARES_LIB_INIT_ALL);
  if (status != ARES_SUCCESS) {
    return 0;
  }

  status = ares_init(&channel);
  if (status != ARES_SUCCESS) {
    ares_library_cleanup();
    return 0;
  }

  hints.ai_flags = ARES_AI_CANONNAME;
  hints.ai_family = AF_UNSPEC;
  hints.ai_socktype = SOCK_STREAM;
  hints.ai_protocol = IPPROTO_TCP;

  ares_getaddrinfo_ext(channel, "example.com", "80", &hints, nullptr, nullptr);

  // Call the missing function
  ares_getaddrinfo_int(channel->data, "example.com", "80", &hints, nullptr, nullptr);

  ares_destroy(channel);
  ares_library_cleanup();

  return 0;
}