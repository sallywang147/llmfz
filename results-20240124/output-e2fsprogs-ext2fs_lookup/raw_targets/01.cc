 #include <stddef.h>
#include <stdint.h>
#include <unistd.h>
#include <assert.h>
#include <sys/syscall.h>
#include <linux/memfd.h>
#include <fuzzer/FuzzedDataProvider.h>

#include "ext2fs/ext2fs.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {

  FuzzedDataProvider stream(data, size);
  const int dir = stream.ConsumeIntegral<int>();
  const int namelen = stream.ConsumeIntegral<int>();
  std::string name = stream.ConsumeBytesAsString(namelen);
  std::string buf = stream.ConsumeRemainingBytesAsString();
  int inode = 0;

  // Write our data to a temp file.
  int fd = syscall(SYS_memfd_create, "ext2_test_file", 0);
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
    ext2fs_lookup(&fs, dir, (char*) name.c_str(), namelen, (char*) buf.c_str(), &inode);
    ext2fs_close(fs);
  }
  close(fd);

  return 0;
}