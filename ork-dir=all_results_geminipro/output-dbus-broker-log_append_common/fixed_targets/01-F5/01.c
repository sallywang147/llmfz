#include <stddef.h>
#include <stdint.h>
#include <string.h>

#include "log.h"

extern "C" {
#include <stdlib.h>
}

void LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  struct Log log = {0};
  int level = 0;
  int error = 0;
  char *id = NULL;
  char *file = NULL;
  int line = 0;
  char *func = NULL;
  size_t offset = 0;

  if (size < sizeof(log))
    return;

  memcpy(&log, data, sizeof(log));
  offset += sizeof(log);

  if (offset + sizeof(int) > size)
    return;

  memcpy(&level, data + offset, sizeof(int));
  offset += sizeof(int);

  if (offset + sizeof(int) > size)
    return;

  memcpy(&error, data + offset, sizeof(int));
  offset += sizeof(int);

  if (offset + sizeof(size_t) > size)
    return;

  size_t id_len = 0;
  memcpy(&id_len, data + offset, sizeof(size_t));
  offset += sizeof(size_t);

  if (offset + id_len + 1 > size)
    return;

  id = (char *)malloc(id_len + 1);
  memcpy(id, data + offset, id_len);
  id[id_len] = '\0';
  offset += id_len + 1;

  if (offset + sizeof(size_t) > size)
    return;

  size_t file_len = 0;
  memcpy(&file_len, data + offset, sizeof(size_t));
  offset += sizeof(size_t);

  if (offset + file_len + 1 > size)
    return;

  file = (char *)malloc(file_len + 1);
  memcpy(file, data + offset, file_len);
  file[file_len] = '\0';
  offset += file_len + 1;

  if (offset + sizeof(int) > size)
    return;

  memcpy(&line, data + offset, sizeof(int));
  offset += sizeof(int);

  if (offset + sizeof(size_t) > size)
    return;

  size_t func_len = 0;
  memcpy(&func_len, data + offset, sizeof(size_t));
  offset += sizeof(size_t);

  if (offset + func_len + 1 > size)
    return;

  func = (char *)malloc(func_len + 1);
  memcpy(func, data + offset, func_len);
  func[func_len] = '\0';
  offset += func_len + 1;

  log_append_common(&log, level, error, id, file, line, func);

  free(id);
  free(file);
  free(func);
}