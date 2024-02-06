#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "ext2fs/ext2fs.h"

// Define a test function to pass to ext2fs_dir_iterate2
int test_func(struct ext2_dir_entry *dirent, int offset, int blocksize, char *buf, void *priv_data) {
    return 0;
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  static bool initialized = false;
  if (!initialized) {
    ext2fs_initialize("fuzz", EXT2_FLAG_RW, NULL, NULL, NULL);
    initialized = true;
  }

  FuzzedDataProvider stream(data, size);

  // Initialize the required parameters for ext2fs_dir_iterate2
  struct struct_ext2_filsys *fs = NULL;
  int dir = stream.ConsumeIntegral<int>();
  int flags = stream.ConsumeIntegral<int>();
  size_t block_buf_size = stream.ConsumeIntegralInRange<size_t>(0, 4096);
  std::vector<char> block_buf(block_buf_size);
  func_type *func = test_func;
  std::string priv_data_str = stream.ConsumeRandomLengthString();
  char *priv_data = const_cast<char*>(priv_data_str.c_str());

  // Call the function to fuzz
  ext2fs_dir_iterate2(fs, dir, flags, block_buf.data(), func, priv_data);

  return 0;
}