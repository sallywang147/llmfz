#include <fuzzer/FuzzedDataProvider.h>
#include "H5Dpkg.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  if(size < sizeof(H5D_io_info_t) + sizeof(H5D_dset_io_info_t))
    return 0;

  FuzzedDataProvider stream(data, size);

  H5D_io_info_t io_info;
  H5D_dset_io_info_t dset_io_info;

  stream.ConsumeData(&io_info, sizeof(io_info));
  stream.ConsumeData(&dset_io_info, sizeof(dset_io_info));

  H5D__virtual_read(&io_info, &dset_io_info);

  return 0;
}