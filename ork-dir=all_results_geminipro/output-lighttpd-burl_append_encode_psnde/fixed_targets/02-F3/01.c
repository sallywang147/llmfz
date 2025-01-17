#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "buffer.h"
#include "burl.h"

#include "burl_encode.h"

void run_burl_append_encode_psnde(buffer *b, char *str, size_t len, int line) {
  burl_append_encode_psnde(b, str, len);
}

int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  if (size <= 4) {
    return 0;
  }
  data += 4;
  size -= 4;
  char *new_str = (char *)malloc(size + 1);
  if (new_str == NULL) {
    return 0;
  }
  memcpy(new_str, data, size);
  new_str[size] = '\0';

  /* main fuzzer entrypoint for library */
  buffer *b = buffer_init();
  run_burl_append_encode_psnde(b, new_str, size, __LINE__);

  buffer_free(b);
  free(new_str);
  return 0;
}