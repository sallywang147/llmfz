#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "buffer.h"
#include "burl.h"

void run_burl_append_encode_all(buffer *b, char *str, size_t len, int line) {
  buffer_reset(b);
  burl_append_encode_all(b, str, len);
}

int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  if (size <= 4) {
    return 0;
  }
  size_t str_len = ((size_t *)data)[0];
  data += 4;
  size -= 4;
  if (str_len >= size) {
    return 0;
  }
  char *new_str = (char *)malloc(str_len + 1);
  if (new_str == NULL) {
    return 0;
  }
  memcpy(new_str, data, str_len);
  new_str[str_len] = '\0';

  /* main fuzzer entrypoint for library */
  buffer *b = buffer_init();
  run_burl_append_encode_all(b, new_str, str_len, __LINE__);

  buffer_free(b);
  free(new_str);
  return 0;
}