#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "buffer.h"
#include "burl.h"

extern "C" {
#include "burl_psnde.h"
}

void run_burl_append_encode_psnde(buffer *psrc, char *str, size_t len, int line, const char *in, size_t in_len) {
  buffer_copy_string_len(psrc, in, in_len);
  burl_append_encode_psnde(psrc, str, len);
}

int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  if (size <= 4) {
    return 0;
  }
  int len = ((int *)data)[0];
  data += 4;
  size -= 4;
  char *new_str = (char *)malloc(size + 1);
  if (new_str == NULL) {
    return 0;
  }
  memcpy(new_str, data, size);
  new_str[size] = '\0';

  /* main fuzzer entrypoint for library */
  buffer *psrc = buffer_init();
  run_burl_append_encode_psnde(psrc, new_str, len, __LINE__, new_str, size);

  buffer_free(psrc);
  free(new_str);
  return 0;
}