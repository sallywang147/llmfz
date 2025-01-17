#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "APFSFSCompat.h"

struct TSK_FS_FILE {
  int size;
  char* data;
};

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  // Initialize APFSFSCompat object
  APFSFSCompat apfsfscompat;

  // Initialize TSK_FS_FILE structure
  TSK_FS_FILE file;
  file.size = stream.ConsumeIntegral<int>();
  std::string file_data = stream.ConsumeRemainingBytesAsString();
  file.data = const_cast<char*>(file_data.c_str());

  // Call the target function
  apfsfscompat.load_attrs(&apfsfscompat, &file);

  return 0;
}