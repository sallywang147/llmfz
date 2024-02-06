#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "libexif/exif-data.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  
  // Create a temporary file and write the data to it.
  char file_path[] = "/tmp/fuzz-XXXXXX";
  int fd = mkstemp(file_path);
  if (fd < 0) {
    return 0;
  }
  std::vector<uint8_t> buffer = stream.ConsumeRemainingBytes<uint8_t>();
  write(fd, buffer.data(), buffer.size());
  close(fd);

  // Call the function to be fuzzed.
  ExifData *exif_data = exif_data_new_from_file(file_path);

  // Clean up.
  if (exif_data) {
    exif_data_unref(exif_data);
  }
  remove(file_path);

  return 0;
}