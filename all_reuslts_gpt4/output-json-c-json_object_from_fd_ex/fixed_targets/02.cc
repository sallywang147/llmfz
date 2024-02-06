#include <stdint.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#include <json.h>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  // Create a temporary file and write the data into it
  char filename[] = "/tmp/fuzz.XXXXXX";
  int fd = mkstemp(filename);
  if (fd < 0) {
    return 0;
  }
  write(fd, data, size);
  lseek(fd, 0, SEEK_SET);  // Reset the file descriptor to the beginning

  // Parse the JSON from the file
  json_object *obj = json_object_from_fd_ex(fd, JSON_TOKENER_DEFAULT_DEPTH);

  if (obj != nullptr) {
    if (json_object_is_type(obj, json_type_object)) {
      json_object_object_foreach(obj, key, val) {
        (void)json_object_get_type(val);
        (void)json_object_get_string(val);
      }
    }
    (void)json_object_to_json_string_ext(obj, JSON_C_TO_STRING_PRETTY | JSON_C_TO_STRING_SPACED);

    json_object_put(obj);
  }

  close(fd);
  unlink(filename);  // Delete the temporary file

  return 0;
}