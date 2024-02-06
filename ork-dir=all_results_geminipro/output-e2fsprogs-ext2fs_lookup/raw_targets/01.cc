#include <fuzzer/FuzzedDataProvider.h>

#include <assert.h>
#include <errno.h>
#include <fcntl.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/syscall.h>
#include <unistd.h>

#include "ext2fs/ext2fs.h"
extern "C" {
#include "e2p/e2p.h"
#include "support/print_fs_flags.h"
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {

  const char *progname = "ext2fs_lookup_fuzzer";
  add_error_table(&et_ext2_error_table);

  FuzzedDataProvider stream(data, size);
  const int dir = stream.ConsumeIntegral<int>();
  const int namelen = stream.ConsumeIntegralInRange<int>(0, 1024);
  std::vector<char> name = stream.ConsumeBytes<char>(namelen);
  const int buflen = stream.ConsumeIntegralInRange<int>(0, 1024);
  std::vector<char> buf = stream.ConsumeBytes<char>(buflen);
  int *inode = (int *)malloc(sizeof(int));

  static const char *fname = "/tmp/ext2_test_file";

  // Write our data to a temp file.
#ifdef SAVE_FS_IMAGE
  int fd = open(fname, O_CREAT | O_TRUNC | O_RDWR, 0644);
#else
  int fd = syscall(SYS_memfd_create, fname, 0);
#endif
  std::vector<char> buffer = stream.ConsumeRemainingBytes<char>();
  write(fd, buffer.data(), buffer.size());

  std::string fspath("/proc/self/fd/" + std::to_string(fd));

  ext2_filsys fs;
  errcode_t retval = ext2fs_open(fspath.c_str(), EXT2_FLAG_RW | EXT2_FLAG_IGNORE_CSUM_ERRORS, 0, 0, unix_io_manager, &fs);

  if (retval) {
    com_err(progname, retval, "while trying to open file system");
  } else {
    retval = ext2fs_lookup(fs, dir, name.data(), namelen, buf.data(), inode);
    if (retval) {
      com_err(progname, retval, "while trying to lookup file");
    }
    ext2fs_close(fs);
  }
  close(fd);
  free(inode);

  return 0;
}