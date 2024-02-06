#include "hiredis.h"
#include <stdlib.h>
#include <string.h>
#include <va_list>

int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  char *new_str, *cmd;
  std::va_list ap;

  if (size < 3)
    return 0;

  new_str = malloc(size + 1);
  if (new_str == NULL)
    return 0;

  memcpy(new_str, data, size);
  new_str[size] = '\0';

  va_start(ap, new_str);
  if (redisvCommand(NULL, new_str, &ap) != NULL)
    hi_free(cmd);
  va_end(ap);

  free(new_str);
  return 0;
}