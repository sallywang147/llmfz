#include <fuzzer/FuzzedDataProvider.h>
#include <ext2fs/ext2fs.h>
#include <stdint.h>
#include <stdlib.h>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider stream(data, size);

  static bool initialized = false;
  if (!initialized) {
    ext2fs_initialize("fuzz", 0, 1024, NULL, NULL);
    initialized = true;
  }

  struct struct_ext2_filsys *fs;
  int dir = stream.ConsumeIntegral<int>();
  int namelen = stream.ConsumeIntegralInRange<int>(1, 255);
  std::string name = stream.ConsumeBytesAsString(namelen);
  char *buf = (char *)malloc(namelen + 1);
  int inode;

  if (ext2fs_open("fuzz", 0, 0, 0, unix_io_manager, &fs) != 0) {
    free(buf);
    return 0;
  }

  ext2fs_lookup(fs, dir, const_cast<char *>(name.c_str()), namelen, buf, &inode);

  ext2fs_close(fs);
  free(buf);

  return 0;
}