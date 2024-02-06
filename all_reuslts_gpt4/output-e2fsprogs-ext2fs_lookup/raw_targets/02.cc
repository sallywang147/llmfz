#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "ext2fs/ext2_fs.h"
#include "ext2fs/ext2fs.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  static struct struct_ext2_filsys *fs = NULL;
  if (fs == NULL) {
    errcode_t err = ext2fs_read_mem(0, 1024, EXT2_FLAG_RW, "test", &fs);
    if (err) {
      fprintf(stderr, "ext2fs_read_mem failed: %d\n", err);
      return 0;
    }
  }

  FuzzedDataProvider provider(data, size);
  
  int dir = provider.ConsumeIntegral<int>();
  int namelen = provider.ConsumeIntegralInRange<int>(0, provider.remaining_bytes() / 2);
  std::string name = provider.ConsumeBytesAsString(namelen);
  int buflen = provider.ConsumeIntegralInRange<int>(0, provider.remaining_bytes());
  std::string buf = provider.ConsumeBytesAsString(buflen);
  int inode;
  
  ext2fs_lookup(fs, dir, const_cast<char*>(name.c_str()), namelen, const_cast<char*>(buf.c_str()), &inode);

  return 0;
}