#include <stddef.h>

#include <ares.h>

extern "C" {
#include <arpa/inet.h>
#include <netdb.h>
#include <sys/socket.h>
}

int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  ares_channel channel;
  ares_init(&channel);

  ares_getaddrinfo(&channel, "www.example.com", NULL, NULL, NULL, NULL);

  ares_destroy(&channel);

  return 0;
}