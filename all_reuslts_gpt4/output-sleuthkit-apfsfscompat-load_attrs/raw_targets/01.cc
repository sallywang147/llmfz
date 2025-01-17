#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>

#include "APFSFSCompat.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  
  // Create an instance of APFSFSCompat
  APFSFSCompat apfsCompat;

  // Create an instance of TSK_FS_FILE and populate it with fuzzed data
  TSK_FS_FILE file;
  file.name = stream.ConsumeRandomLengthString().c_str();
  file.meta = nullptr; // We're not fuzzing this part
  file.fs_info = nullptr; // We're not fuzzing this part
  file.tag = stream.ConsumeIntegral<uint16_t>();
  file.nlink = stream.ConsumeIntegral<uint16_t>();
  file.action = stream.ConsumeIntegral<uint8_t>();
  file.flags = stream.ConsumeIntegral<uint8_t>();
  file.name_nuls = stream.ConsumeIntegral<uint8_t>();
  file.attr_state = stream.ConsumeIntegral<uint8_t>();

  // Call the function under test
  apfsCompat.load_attrs(&apfsCompat, &file);

  return 0;
}