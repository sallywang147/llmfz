#include <stdint.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#include <json.h>
#include <fuzzer/FuzzedDataProvider.h>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider stream(data, size);
  
  // Create a temporary file and write the data into it
  char filename[] = "/tmp/fuzz-XXXXXX";
  int fd = mkstemp(filename);
  if (fd < 0) {
    return 0;
  }
  write(fd, data, size);
  lseek(fd, 0, SEEK_SET);

  // Consume an integer for in_depth parameter
  int in_depth = stream.ConsumeIntegral<int>();

  // Call the function
  json_object *obj = json_object_from_fd_ex(fd, in_depth);

  // Clean up
  if (obj != nullptr) {
    json_object_put(obj);
  }
  close(fd);
  unlink(filename);

  return 0;
}