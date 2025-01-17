#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "buffer.h"
#include "burl.h"

extern "C" {
#include "burl_encode.h"
#include "burl_encode_psnde.h"
}

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
```

The issue was that the `burl_encode.h` header was not wrapped in `extern "C" {}`. This caused the linker to be unable to find the definition of `burl_append_encode_psnde`.

To fix the issue, the `burl_encode.h` header was wrapped in `extern "C" {}`. This tells the linker that the functions and variables declared in that header are written in C, not C++. This allows the linker to find the definition of `burl_append_encode_psnde` and successfully link the program.