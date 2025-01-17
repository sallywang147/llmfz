#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <vector>

#include "H5Dpkg.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  // Initialize the library
  H5open();

  // Create objects for the function parameters
  struct H5D_t *dset = NULL;
  struct H5O_storage_virtual_t *storage = NULL;
  struct H5S_t *file_space = NULL;
  struct H5S_t *mem_space = NULL;
  size_t nelmts = stream.ConsumeIntegral<size_t>();

  // Call the function with the initialized parameters
  H5D__virtual_pre_io(dset, storage, file_space, mem_space, &nelmts);

  // Close the library
  H5close();

  return 0;
}