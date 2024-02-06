#include <fuzzer/FuzzedDataProvider.h>
#include "hdf5.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider stream(data, size);

  struct H5D_io_info_t io_info;
  struct H5D_dset_io_info_t dset_io_info;

  // Initialize the structures with data from the fuzzed input
  if (stream.remaining_bytes() < sizeof(io_info) + sizeof(dset_io_info)) {
    return 0;
  }

  stream.ConsumeData(&io_info, sizeof(io_info));
  stream.ConsumeData(&dset_io_info, sizeof(dset_io_info));

  // Call the function to be fuzzed
  H5D__virtual_write(&io_info, &dset_io_info);

  return 0;
}