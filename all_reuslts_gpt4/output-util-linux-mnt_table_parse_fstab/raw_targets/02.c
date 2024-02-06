#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "libmount/libmount.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  // Create a new table
  struct libmnt_table *tb = mnt_new_table();
  if (!tb) {
    return 0;
  }

  // Create a temporary file with the fuzzing data
  char filename[] = "/tmp/fuzz.XXXXXX";
  int fd = mkstemp(filename);
  if (fd < 0) {
    mnt_free_table(tb);
    return 0;
  }

  // Write the fuzzing data to the file
  std::vector<uint8_t> bytes = stream.ConsumeRemainingBytes<uint8_t>();
  write(fd, bytes.data(), bytes.size());
  close(fd);

  // Parse the file
  mnt_table_parse_fstab(tb, filename);

  // Clean up
  remove(filename);
  mnt_free_table(tb);

  return 0;
}