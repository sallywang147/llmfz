#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include "civetweb.h"

extern "C" {
int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  char *host = (char *)malloc(size + 1);
  memcpy(host, data, size);
  host[size] = '\0';
  char *ebuf = (char *)malloc(256);
  mg_download(host, 80, 0, ebuf, 256, "GET / HTTP/1.0\r\n\r\n");
  free(host);
  free(ebuf);
  return 0;
}
}