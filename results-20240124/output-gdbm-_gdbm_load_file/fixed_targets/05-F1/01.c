#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <vector>

#include "gdbm.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider provider(data, size);

  // Create a temporary file to store the input data.
  char tmp_file_name[] = "/tmp/gdbm_fuzzer_XXXXXX";
  int fd = mkstemp(tmp_file_name);
  if (fd == -1) {
    perror("mkstemp");
    return 0;
  }

  // Write the input data to the temporary file.
  if (write(fd, data, size) != (ssize_t)size) {
    perror("write");
    close(fd);
    return 0;
  }

  // Seek to the beginning of the file.
  if (lseek(fd, 0, SEEK_SET) == -1) {
    perror("lseek");
    close(fd);
    return 0;
  }

  // Create a dump file object.
  struct dump_file file;
  file.df_fd = fd;
  file.df_pos = 0;
  file.df_size = size;

  // Create a gdbm file info object.
  struct gdbm_file_info dbf;
  memset(&dbf, 0, sizeof(dbf));

  // Create a pointer to the gdbm file info object.
  struct gdbm_file_info *ofp = &dbf;

  // Call the _gdbm_load_file function.
  int ret = _gdbm_load_file(&file, &dbf, &ofp, 0, 0);

  // Close the temporary file.
  close(fd);

  // Return the return value of the _gdbm_load_file function.
  return ret;
}