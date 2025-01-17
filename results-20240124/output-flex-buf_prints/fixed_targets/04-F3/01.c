#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "buf.h"

struct Buf {
  size_t len;
  char *data;
};

struct Buf *buf_new(size_t initial_size) {
  struct Buf *buf = malloc(sizeof(struct Buf));
  if (buf == NULL) {
    return NULL;
  }
  buf->len = 0;
  buf->data = malloc(initial_size);
  if (buf->data == NULL) {
    free(buf);
    return NULL;
  }
  return buf;
}

void buf_free(struct Buf *buf) {
  free(buf->data);
  free(buf);
}

size_t buf_len(struct Buf *buf) {
  return buf->len;
}

char *buf_data(struct Buf *buf) {
  return buf->data;
}

int buf_append(struct Buf *buf, const char *data, size_t len) {
  size_t new_len = buf->len + len;
  char *new_data = realloc(buf->data, new_len);
  if (new_data == NULL) {
    return -1;
  }
  memcpy(new_data + buf->len, data, len);
  buf->data = new_data;
  buf->len = new_len;
  return 0;
}

struct Buf *buf_prints(struct Buf *buf, char *fmt, char *s) {
  int len = snprintf(NULL, 0, fmt, s);
  if (len < 0) {
    return NULL;
  }
  if (buf_append(buf, fmt, len) != 0) {
    return NULL;
  }
  return buf;
}

int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  struct Buf *buf = buf_new(1024);
  if (buf == NULL) {
    return 0;
  }
  buf_prints(buf, "%s", data);
  buf_free(buf);
  return 0;
}