#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#include <json.h>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  // Create a temporary file and write the data to it
  char filename[] = "/tmp/fuzz-XXXXXX";
  int fd = mkstemp(filename);
  if (fd < 0) {
    return 0;
  }
  write(fd, data, size);
  close(fd);

  // Call the target function
  json_object *obj = json_object_from_file(filename);

  // Process the json object
  if (obj) {
    (void)json_object_to_json_string_ext(obj, JSON_C_TO_STRING_PRETTY | JSON_C_TO_STRING_SPACED);
    json_object_put(obj);
  }

  // Clean up
  remove(filename);

  return 0;
}