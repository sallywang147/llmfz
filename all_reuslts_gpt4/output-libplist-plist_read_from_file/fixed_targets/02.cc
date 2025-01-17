#include <fuzzer/FuzzedDataProvider.h>
#include <plist/plist.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider stream(data, size);
  std::string filename = stream.ConsumeRandomLengthString();
  char *plist = nullptr;
  int format = 0;

  // Create a temporary file and write the data to it.
  char temp_filename[] = "/tmp/fuzzedfileXXXXXX";
  int fd = mkstemp(temp_filename);
  if (fd < 0) {
    return 0;
  }
  write(fd, filename.c_str(), filename.size());
  close(fd);

  // Call the function to be fuzzed.
  plist_read_from_file(temp_filename, &plist, &format);

  // Clean up.
  free(plist);
  remove(temp_filename);

  return 0;
}