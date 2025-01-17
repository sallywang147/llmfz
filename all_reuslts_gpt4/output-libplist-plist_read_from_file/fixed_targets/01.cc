#include <fuzzer/FuzzedDataProvider.h>
#include <plist/plist.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  if (size == 0) {
    return 0;
  }

  FuzzedDataProvider stream(data, size);

  // Create a temporary file and write the data to it.
  char filename[] = "/tmp/fuzz-XXXXXX";
  int fd = mkstemp(filename);
  if (fd < 0) {
    return 0;
  }
  FILE *file = fdopen(fd, "wb");
  if (!file) {
    close(fd);
    return 0;
  }
  fwrite(data, 1, size, file);
  fclose(file);

  // Call the target function.
  char *plist = nullptr;
  int format = 0;
  plist_read_from_file(filename, &plist, &format);

  // Clean up.
  free(plist);
  remove(filename);

  return 0;
}