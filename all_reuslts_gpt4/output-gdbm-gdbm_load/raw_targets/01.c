#include <fuzzer/FuzzedDataProvider.h>
#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <gdbm.h>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider stream(data, size);

  // Initialize gdbm_file_info pointer
  struct gdbm_file_info *pdbf = nullptr;

  // Extract filename from the fuzzed data
  std::string filename = stream.ConsumeRandomLengthString();
  
  // Extract replace from the fuzzed data
  int replace = stream.ConsumeIntegral<int>();

  // Extract meta_mask from the fuzzed data
  int meta_mask = stream.ConsumeIntegral<int>();

  // Initialize line
  size_t line = 0;

  // Call the function to be fuzzed
  gdbm_load(&pdbf, const_cast<char *>(filename.c_str()), replace, meta_mask, &line);

  return 0;
}