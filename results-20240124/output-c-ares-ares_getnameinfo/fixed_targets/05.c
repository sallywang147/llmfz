#include <stddef.h>
#include <ares.h>

extern "C" {
#include "ares_setup.h"
#include <sys/time.h> // Include the definition of timeval
}

// Entrypoint for Clang's libfuzzer
int LLVMFuzzerTestOneInput(const unsigned char *data,
                           unsigned long size) {
  // Feed the data into each of the ares_parse_*_reply functions.
  ares_channel channel;
  int status = ares_init(&channel);
  if (status != ARES_SUCCESS) {
    return 0;
  }
  ares_getnameinfo(&channel, NULL, 0, 0, NULL, NULL);
  ares_destroy(&channel);
  return 0;
}