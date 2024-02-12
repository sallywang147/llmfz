#include <stddef.h>
#include <cstring>

#include "ares.h"

// Entrypoint for Clang's libfuzzer
extern "C" int LLVMFuzzerTestOneInput(const unsigned char *data,
                           unsigned long size) {
  struct ares_addrinfo_hints hints;
  memset(&hints, 0, sizeof(hints));
  hints.ai_family = AF_INET;
  char *name = (char*)data;
  char *service = (char*)data;
  char *callback_name = (char*)data;
  ares_getaddrinfo_int(NULL, name, service, &hints, NULL, callback_name);
  return 0;
}