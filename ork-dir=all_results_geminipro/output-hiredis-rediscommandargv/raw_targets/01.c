#include "hiredis.h"
#include <stdlib.h>
#include <string.h>

int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  char *new_str, **argv;
  size_t *argvlen;
  int argc;

  if (size < 3)
    return 0;

  new_str = malloc(size + 1);
  if (new_str == NULL)
    return 0;

  memcpy(new_str, data, size);
  new_str[size] = '\0';

  argv = &new_str;
  argc = 1;
  argvlen = NULL;

  redisCommandArgv(NULL, argc, argv, argvlen);

  free(new_str);
  return 0;
}