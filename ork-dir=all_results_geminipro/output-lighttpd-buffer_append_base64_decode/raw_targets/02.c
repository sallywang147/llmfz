#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "buffer.h"
#include "base64.h"

void run_buffer_append_base64_decode(buffer *out, char *in, size_t in_length, int charset, int line, const char *in_str, size_t in_str_len) {
  buffer_copy_string_len(out, in_str, in_str_len);
  char *ret = buffer_append_base64_decode(out, in, in_length, charset);
}

int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  if (size <= 4) {
    return 0;
  }
  int charset = ((int *)data)[0];
  data += 4;
  size -= 4;
  char *new_str = (char *)malloc(size + 1);
  if (new_str == NULL) {
    return 0;
  }
  memcpy(new_str, data, size);
  new_str[size] = '\0';

  /* main fuzzer entrypoint for library */
  buffer *out = buffer_init();
  run_buffer_append_base64_decode(out, new_str, size, charset, __LINE__, new_str, size);

  buffer_free(out);
  free(new_str);
  return 0;
}