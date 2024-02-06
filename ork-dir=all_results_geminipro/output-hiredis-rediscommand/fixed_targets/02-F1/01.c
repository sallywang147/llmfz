#include "hiredis.h"
#include <stdlib.h>
#include <string.h>

extern "C" {
#include <hiredis/hiredis.h>
}

int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  char *new_str, *reply;
  struct redisContext *c;

  if (size < 3)
    return 0;

  new_str = malloc(size + 1);
  if (new_str == NULL)
    return 0;

  memcpy(new_str, data, size);
  new_str[size] = '\0';

  c = redisConnect("localhost", 6379);
  if (c == NULL) {
    free(new_str);
    return 0;
  }

  reply = redisCommand(c, new_str);
  if (reply != NULL) {
    freeReplyObject(reply);
  }

  redisFree(c);
  free(new_str);
  return 0;
}