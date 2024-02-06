#include <fuzzer/FuzzedDataProvider.h>
#include <ext2fs/ext2fs.h>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider stream(data, size);

  // Initialize filesystem
  struct struct_ext2_filsys fs;
  fs.blocksize = 1024;
  fs.device_name = const_cast<char*>("fuzzing_device");
  fs.super = static_cast<struct ext2_super_block*>(calloc(1, sizeof(struct ext2_super_block)));
  fs.io = static_cast<io_manager>(calloc(1, sizeof(struct struct_io_manager)));

  // Consume data for the function parameters
  int dir = stream.ConsumeIntegral<int>();
  std::string name = stream.ConsumeRandomLengthString();
  int ino = stream.ConsumeIntegral<int>();
  int flags = stream.ConsumeIntegral<int>();

  // Call the function under test
  ext2fs_link(&fs, dir, const_cast<char*>(name.c_str()), ino, flags);

  // Clean up
  free(fs.super);
  free(fs.io);

  return 0;
}