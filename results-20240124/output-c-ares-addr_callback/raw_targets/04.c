 #include <stddef.h>

#include "ares.h"

// Entrypoint for Clang's libfuzzer
int LLVMFuzzerTestOneInput(const unsigned char *data,
                           unsigned long size) {
  // Feed the data into each of the ares_parse_*_reply functions.
  ares_addr_callback(data, size, 1, data, size);
  return 0;
}