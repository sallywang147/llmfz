#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "ext2fs/ext2fs.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  // As we don't have control over the file system creation, we use a static fs
  static struct struct_ext2_filsys *fs = NULL;
  if (fs == NULL) {
    errcode_t err = ext2fs_init_mem(&fs, 4096, 0);
    if (err != 0) {
      return 0;
    }
  }

  // Consume data to create parameters for ext2fs_link
  int dir = stream.ConsumeIntegral<int>();
  std::string name = stream.ConsumeRandomLengthString();
  int ino = stream.ConsumeIntegral<int>();
  int flags = stream.ConsumeIntegral<int>();

  // Call the function with the fuzzed parameters
  ext2fs_link(fs, dir, const_cast<char*>(name.c_str()), ino, flags);

  return 0;
}