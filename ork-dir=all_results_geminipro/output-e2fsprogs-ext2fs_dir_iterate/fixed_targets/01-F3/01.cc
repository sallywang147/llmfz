#include <assert.h>
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

  const char *progname = "ext2fs_image_read_write_fuzzer";
  add_error_table(&et_ext2_error_table);

  enum FuzzerType { ext2fsImageBitmapRead, ext2fsImageInodeRead, ext2fsImageSuperRead, ext2fsImageBitmapWrite, ext2fsImageInodeWrite, ext2fsImageSuperWrite, ext2fsDirIterate, kMaxValue = ext2fsDirIterate };

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
    case ext2fsImageBitmapRead: {
      retval = ext2fs_image_bitmap_read(fs, fd, 0);
      if (retval)
        com_err(progname, retval, "while trying to read image bitmap");
      break;
    }
    case ext2fsImageInodeRead: {
      retval = ext2fs_image_inode_read(fs, fd, 0);
      if (retval)
        com_err(progname, retval, "while trying to read image inode");
      break;
    }
    case ext2fsImageSuperRead: {
      retval = ext2fs_image_super_read(fs, fd, 0);
      if (retval)
        com_err(progname, retval, "while trying to read image superblock");
      break;
    }
    case ext2fsImageBitmapWrite: {
      retval = ext2fs_image_bitmap_write(fs, fd, 0);
      if (retval)
        com_err(progname, retval, "while trying to write image bitmap");
      break;
    }
    case ext2fsImageInodeWrite: {
      retval = ext2fs_image_inode_write(fs, fd, 0);
      if (retval)
        com_err(progname, retval, "while trying to write image inode");
      break;
    }
    case ext2fsImageSuperWrite: {
      retval = ext2fs_image_super_write(fs, fd, 0);
      if (retval)
        com_err(progname, retval, "while trying to write image superblock");
      break;
    }
    case ext2fsDirIterate: {
      retval = ext2fs_dir_iterate(fs, 0, flags, 0, 0, 0);
      if (retval)
        com_err(progname, retval, "while trying to iterate directory");
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