#include <fuzzer/FuzzedDataProvider.h>
#include <ext2fs/ext2fs.h>

#include <cstddef>
#include <cstdint>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  static bool initialized = false;
  if (!initialized) {
    ext2fs_initialize("fuzz", 0, 1024, NULL, NULL);
    initialized = true;
  }

  ext2_filsys fs;
  int parent = stream.ConsumeIntegral<int>();
  int ino = stream.ConsumeIntegral<int>();

  std::string name = stream.ConsumeRandomLengthString();
  std::string target = stream.ConsumeRemainingBytesAsString();

  ext2fs_symlink(fs, parent, ino, const_cast<char*>(name.c_str()), const_cast<char*>(target.c_str()));

  return 0;
}