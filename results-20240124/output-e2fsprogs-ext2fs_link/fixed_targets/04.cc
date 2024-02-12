 #include <stddef.h>
#include <stdint.h>
#include <unistd.h>
#include <assert.h>
#include <sys/syscall.h>
#include <linux/memfd.h>
#include <fuzzer/FuzzedDataProvider.h>

#include "ext2fs/ext2fs.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {

  enum FuzzerType {
    ext2fsImageBitmapRead,
    ext2fsImageInodeRead,
    ext2fsImageSuperRead,
    ext2fsImageBitmapWrite,
    ext2fsImageInodeWrite,
    ext2fsImageSuperWrite,
    ext2fsLink,
    kMaxValue = ext2fsLink
  };

  FuzzedDataProvider stream(data, size);
  const FuzzerType f = stream.ConsumeEnum<FuzzerType>();
  (void) stream.ConsumeIntegral<int>();
  // Keep this here to not spoil the corpus or reproducers

  static const char* fname = "ext2_test_file";

  // Write our data to a temp file.
  int fd = syscall(SYS_memfd_create, fname, 0);
  std::vector<char> buffer = stream.ConsumeRemainingBytes<char>();
  write(fd, buffer.data(), buffer.size());

  std::string fspath("/proc/self/fd/" + std::to_string(fd));

  ext2_filsys fs;
  errcode_t retval = ext2fs_open(
      fspath.c_str(),
      EXT2_FLAG_IGNORE_CSUM_ERRORS, 0, 0,
      unix_io_manager,
      &fs);

  if (!retval) {
    switch (f) {
      case ext2fsImageBitmapRead: {
        ext2fs_image_bitmap_read(fs, fd, 0);
        break;
      }
      case ext2fsImageInodeRead: {
        ext2fs_image_inode_read(fs, fd, 0);
        break;
      }
      case ext2fsImageSuperRead: {
        ext2fs_image_super_read(fs, fd, 0);
        break;
      }
      case ext2fsImageBitmapWrite: {
        ext2fs_image_bitmap_write(fs, fd, 0);
        break;
      }
      case ext2fsImageInodeWrite: {
        ext2fs_image_inode_write(fs, fd, 0);
        break;
      }
      case ext2fsImageSuperWrite: {
        ext2fs_image_super_write(fs, fd, 0);
        break;
      }
      case ext2fsLink: {
        const char* name = stream.ConsumeBytesAsString(stream.ConsumeIntegralInRange<size_t>(0, 100)).c_str();
        ext2fs_link(fs, 0, const_cast<char*>(name), 0, 0);
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