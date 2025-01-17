#include "llhttp.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

extern "C" {
#include "llhttp/llhttp.h"
}

int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  llhttp__internal_t internal;
  memset(&internal, 0, sizeof(internal));

  /* We need four bytes to determine variable parameters */
  if (size < 4) {
    return 0;
  }

  int headers = (data[0] & 0x01) == 1;
  int chunked_length = (data[1] & 0x01) == 1;
  int keep_alive = (data[2] & 0x01) == 1;
  llhttp__type_t http_type;
  if (data[0] % 3 == 0) {
    http_type = HTTP_BOTH;
  } else if (data[0] % 3 == 1) {
    http_type = HTTP_REQUEST;
  } else {
    http_type = HTTP_RESPONSE;
  }
  data += 4;
  size -= 4;

  /* Initialize user callbacks and settings */
  llhttp__settings_t settings;
  llhttp__settings_init(&settings);

  /* Set user callback */
  settings.on_message_complete = NULL;

  llhttp__init(&internal, http_type, &settings);
  llhttp__set_lenient_headers(&internal, headers);
  llhttp__set_lenient_chunked_length(&internal, chunked_length);
  llhttp__set_lenient_keep_alive(&internal, keep_alive);

  llhttp__debug(&internal, (char *)data, (char *)data + size, "fuzz");

  return 0;
}