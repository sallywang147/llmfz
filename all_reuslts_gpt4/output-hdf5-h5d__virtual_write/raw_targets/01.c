#include <fuzzer/FuzzedDataProvider.h>
#include "H5Dpkg.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider stream(data, size);

  // Initialize the H5D_io_info_t structure
  H5D_io_info_t io_info;
  io_info.dset = nullptr;
  io_info.file = nullptr;
  io_info.store = nullptr;
  io_info.u.wbuf = nullptr;

  // Initialize the H5D_dset_io_info_t structure
  H5D_dset_io_info_t dset_io_info;
  dset_io_info.md_io_ops_type = H5D_IO_OP_NO_OP;
  dset_io_info.md_io_ops = nullptr;

  // Call the target function
  H5D__virtual_write(&io_info, &dset_io_info);

  return 0;
}