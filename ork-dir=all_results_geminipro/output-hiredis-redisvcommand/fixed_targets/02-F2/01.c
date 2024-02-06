#include "hiredis.h"
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>

extern "C" {
#include <stdio.h>
}

int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  char *new_str, *cmd;
  struct redisContext *c = redisConnect("localhost", 6379);

  if (c == NULL || c->err) {
    return 0;
  }

  if (size < 3)
    return 0;

  new_str = malloc(size + 1);
  if (new_str == NULL)
    return 0;

  memcpy(new_str, data, size);
  new_str[size] = '\0';

  va_list ap;
  va_start(ap, new_str);
  if (redisvCommand(c, new_str, &ap) != -1)
    hi_free(cmd);
  va_end(ap);

  free(new_str);
  redisFree(c);
  return 0;
}