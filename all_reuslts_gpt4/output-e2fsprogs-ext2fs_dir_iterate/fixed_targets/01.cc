#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "ext2fs/ext2fs.h"

// Define a function of type func_type to be passed to ext2fs_dir_iterate
int dummy_func(struct ext2_dir_entry *dirent, int offset, int blocksize, char *buf, void *priv_data) {
  return 0;
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  // Initialize the ext2 file system
  struct struct_ext2_filsys fs;
  fs.blocksize = stream.ConsumeIntegral<int>();
  fs.device_name = NULL;

  // Get the directory and flags from the stream
  int dir = stream.ConsumeIntegral<int>();
  int flags = stream.ConsumeIntegral<int>();

  // Get the block buffer from the stream
  std::string block_buf = stream.ConsumeRandomLengthString();
  
  // Call ext2fs_dir_iterate with the dummy function and no private data
  ext2fs_dir_iterate(&fs, dir, flags, block_buf.c_str(), dummy_func, NULL);

  return 0;
}