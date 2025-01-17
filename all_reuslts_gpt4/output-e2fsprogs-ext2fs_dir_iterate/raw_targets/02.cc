#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "ext2fs/ext2fs.h"

// Define a function of type func_type
int func(struct ext2_dir_entry *dirent, int offset, int blocksize, char *buf, void *priv_data) {
  return 0;
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  if (size < 2) {
    return 0;
  }

  FuzzedDataProvider stream(data, size);
  int dir = stream.ConsumeIntegral<int>();
  int flags = stream.ConsumeIntegral<int>();
  std::string block_buf = stream.ConsumeRemainingBytesAsString();

  struct struct_ext2_filsys *fs = NULL;
  errcode_t retval;
  retval = ext2fs_initialize("fuzz", EXT2_FLAG_RW, NULL, NULL, NULL, &fs);
  if (retval != 0) {
    return 0;
  }

  ext2fs_dir_iterate(fs, dir, flags, block_buf.data(), func, NULL);

  ext2fs_close(fs);
  return 0;
}