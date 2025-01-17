#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <json.h>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  if (size < 1) {
    return 0;
  }

  // Create a temporary file and write the data to it.
  char filename[] = "/tmp/fuzz.XXXXXX";
  int fd = mkstemp(filename);
  if (fd < 0) {
    return 0;
  }
  FILE *file = fdopen(fd, "wb");
  if (!file) {
    close(fd);
    return 0;
  }
  fwrite(data, size, 1, file);
  fclose(file);

  // Parse the file.
  json_object *obj = json_object_from_file(filename);
  if (obj) {
    // Use the object here.
    (void)json_object_to_json_string_ext(obj, JSON_C_TO_STRING_PRETTY | JSON_C_TO_STRING_SPACED);
    json_object_put(obj);
  }

  // Clean up.
  remove(filename);

  return 0;
}