#include <stdint.h>

#include <json.h>
#include <unistd.h>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  int fd = -1;
  if (size > 0) {
    fd = open("/dev/shm/json_fuzzer_input", O_RDWR | O_CREAT | O_TRUNC, 0600);
    if (fd < 0) {
      return 0;
    }
    write(fd, data, size);
    lseek(fd, 0, SEEK_SET);
  }

  json_object *obj = json_object_from_fd(fd);
  if (obj) {
    (void)json_object_to_json_string_ext(obj, JSON_C_TO_STRING_PRETTY | JSON_C_TO_STRING_SPACED);
    json_object_put(obj);
  }

  if (fd >= 0) {
    close(fd);
  }
  return 0;
}