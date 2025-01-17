#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#ifdef __cplusplus
extern "C" {
#endif

#include "../cJSON.h"

int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size); /* required by C89 */

int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  cJSON *json;
  int format;
  size_t offset = 4;
  int minify, require_termination, formatted, buffered;

  if (size <= offset)
    return 0;
  if (data[size - 1] != '\0')
    return 0;
  if (data[0] != '1' && data[0] != '0')
    return 0;
  if (data[1] != '1' && data[1] != '0')
    return 0;
  if (data[2] != '1' && data[2] != '0')
    return 0;
  if (data[3] != '1' && data[3] != '0')
    return 0;

  minify = data[0] == '1' ? 1 : 0;
  require_termination = data[1] == '1' ? 1 : 0;
  formatted = data[2] == '1' ? 1 : 0;
  buffered = data[3] == '1' ? 1 : 0;

  json = cJSON_ParseWithOpts((const char *)data + offset, NULL, require_termination);

  if (json == NULL)
    return 0;

  if (formatted)
    format = 1;
  else
    format = 0;

  if (buffered) {
    char *printed_json = cJSON_PrintBuffered(json, 1, formatted);
    if (printed_json != NULL)
      free(printed_json);
  } else {
    char *printed_json = cJSON_PrintPreallocated(json, (char *)data + offset, size - offset, format);
    if (printed_json != NULL)
      free(printed_json);
  }

  cJSON_Delete(json);

  return 0;
}

#ifdef __cplusplus
}
#endif