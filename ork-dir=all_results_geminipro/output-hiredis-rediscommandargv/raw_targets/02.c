#include "hiredis.h"
#include <stdlib.h>
#include <string.h>

int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  char *new_str, *cmd;
  size_t argvlen;

  if (size < 3)
    return 0;

  new_str = malloc(size + 1);
  if (new_str == NULL)
    return 0;

  memcpy(new_str, data, size);
  new_str[size] = '\0';

  cmd = redisCommandArgv(NULL, 1, &new_str, &argvlen);
  if (cmd != NULL)
    hi_free(cmd);

  free(new_str);
  return 0;
}