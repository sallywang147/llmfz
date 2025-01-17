#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "libmount/libmount.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  struct libmnt_table *tb = mnt_new_table();
  struct libmnt_table *u_tb = mnt_new_table();

  // Create a temporary file with the fuzzed data.
  char filename[] = "/tmp/fuzz.XXXXXX";
  int fd = mkstemp(filename);
  if (fd < 0) {
    mnt_unref_table(tb);
    mnt_unref_table(u_tb);
    return 0;
  }

  std::vector<uint8_t> fuzzed_data = stream.ConsumeRemainingBytes<uint8_t>();
  write(fd, fuzzed_data.data(), fuzzed_data.size());
  close(fd);

  // Parse the temporary file.
  __mnt_table_parse_mountinfo(tb, filename, u_tb);

  // Cleanup.
  remove(filename);
  mnt_unref_table(tb);
  mnt_unref_table(u_tb);

  return 0;
}