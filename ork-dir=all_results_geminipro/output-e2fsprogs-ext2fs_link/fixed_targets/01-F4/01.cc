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

  const char *progname = "ext2fs_link_fuzzer";
  add_error_table(&et_ext2_error_table);

  enum FuzzerType { ext2fsLink, kMaxValue = ext2fsLink };

  FuzzedDataProvider stream(data, size);
  const FuzzerType f = stream.ConsumeEnum<FuzzerType>();
  int flags = stream.ConsumeIntegral<int>();
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
    printf("FuzzerType: %d\n", (int)f);
    switch (f) {
    case ext2fsLink: {
      const int dir = stream.ConsumeIntegral<int>();
      const char *name = stream.ConsumeRemainingBytes<char>().data();
      const int ino = stream.ConsumeIntegral<int>();
      retval = ext2fs_link(fs, dir, (char *)name, ino, flags);
      if (retval)
        com_err(progname, retval, "while trying to link");
      break;
    }
    default: {
      assert(false);
    }
    }
    ext2fs_close(fs);
  }
  close(fd);

  return 0;
}