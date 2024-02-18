#include <assert.h>
#include <errno.h>
#include <fcntl.h>
#include <fuzzer/FuzzedDataProvider.h>
#include <linux/memfd.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <sys/syscall.h>
#include <unistd.h>

#include "ext2fs/ext2fs.h"
extern "C" {
#include "e2p/e2p.h"
#include "support/print_fs_flags.h"
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {

  const char *progname = "ext2fs_dir_iterate2_fuzzer";
  add_error_table(&et_ext2_error_table);

  FuzzedDataProvider stream(data, size);
  const int flags = stream.ConsumeIntegral<int>();
#ifndef USE_FLAGS
  flags = 0;
#endif

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
#ifdef USE_FLAGS
  printf("Flags: 0x%08x ", flags);
  print_fs_flags(stdout, flags);
  flags &= ~EXT2_FLAG_NOFREE_ON_ERROR;
#endif
  errcode_t retval = ext2fs_open(fspath.c_str(), flags | EXT2_FLAG_IGNORE_CSUM_ERRORS, 0, 0, unix_io_manager, &fs);

  if (retval) {
    com_err(progname, retval, "while trying to open file system");
  } else {
#ifdef DUMP_SUPER
    list_super2(fs->super, stdout);
#endif
    printf("Flags: %d\n", flags);
    retval = ext2fs_dir_iterate2(fs, 0, flags, NULL, NULL, NULL);
    if (retval)
      com_err(progname, retval, "while trying to iterate over directory");
    ext2fs_close(fs);
  }
  close(fd);

  return 0;
}