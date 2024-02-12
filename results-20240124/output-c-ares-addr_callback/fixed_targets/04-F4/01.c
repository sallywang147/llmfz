#include <stddef.h>

#include "ares.h"

extern "C" {
#include <ares_dns.h>
#include <ares_version.h>
}

extern "C" {
int ares_addr_callback(void *arg, int status, struct hostent *hostent);
}

// Entrypoint for Clang's libfuzzer
int LLVMFuzzerTestOneInput(const unsigned char *data,
                           unsigned long size) {
  // Feed the data into each of the ares_parse_*_reply functions.
  ares_addr_callback(data, size, data, size);
  return 0;
}