#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "H5Dpkg.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  struct H5D_t dset;
  struct H5O_storage_virtual_t storage;
  struct H5S_t space1, space2;
  size_t nseq = 0;

  // Initialize the structs with data from the fuzzer
  stream.ConsumeData(&dset, sizeof(dset));
  stream.ConsumeData(&storage, sizeof(storage));
  stream.ConsumeData(&space1, sizeof(space1));
  stream.ConsumeData(&space2, sizeof(space2));
  
  // Call the function under test
  H5D__virtual_pre_io(&dset, &storage, &space1, &space2, &nseq);

  return 0;
}