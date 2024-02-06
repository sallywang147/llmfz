#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "ext2fs/ext2fs.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  
  // Initialize filesystem
  ext2_filsys fs;
  errcode_t err = ext2fs_initialize("fuzz", EXT2_FLAG_RW, 0, NULL, 0, NULL, &fs);
  if (err != 0) {
    return 0;
  }
  
  // Consume data from the stream to use as parameters
  int parent = stream.ConsumeIntegral<int>();
  int ino = stream.ConsumeIntegral<int>();
  std::string name = stream.ConsumeRandomLengthString();
  std::string target = stream.ConsumeRandomLengthString();

  // Call the function under test
  ext2fs_symlink(fs, parent, ino, const_cast<char*>(name.c_str()), const_cast<char*>(target.c_str()));

  // Cleanup
  ext2fs_close_free(&fs);

  return 0;
}