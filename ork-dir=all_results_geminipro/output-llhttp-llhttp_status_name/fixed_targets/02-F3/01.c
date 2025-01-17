#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <llhttp.h>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  if (size < 4) {
    return 0;
  }
  int status_code = data[0] * 256 + data[1];
  data += 4;
  size -= 4;

  char *status_name = llhttp_status_name(status_code);
  if (status_name != NULL) {
    free(status_name);
  }
  return 0;
}