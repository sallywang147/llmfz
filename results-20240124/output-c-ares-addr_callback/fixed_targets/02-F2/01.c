#include <stddef.h>
#include <ares.h>

extern "C" {
// Entrypoint for Clang's libfuzzer
int LLVMFuzzerTestOneInput(const unsigned char *data,
                           unsigned long size) {
  ares_addr_callback addr_callback = [](void *data,
                                      int status,
                                      int timeouts,
                                      char *addr,
                                      int addrlen) {
    // Do nothing.
  };
  ares_addrinfo_callback addrinfo_callback = [](void *data,
                                              int status,
                                              int timeouts,
                                              struct hostent *hostent) {
    // Do nothing.
  };
  ares_channel channel;
  ares_init(&channel);
  ares_gethostbyname(&channel, "example.com", AF_INET, addrinfo_callback,
                     data);
  ares_gethostbyname(&channel, "example.com", AF_INET6, addrinfo_callback,
                     data);
  ares_gethostbyaddr(&channel, data, size, AF_INET, addr_callback, data);
  ares_gethostbyaddr(&channel, data, size, AF_INET6, addr_callback, data);
  ares_destroy(&channel);
  return 0;
}
}