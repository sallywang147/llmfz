#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "hdf5.h"

extern "C" {
#include "hdf5_hl.h"
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  char filename[256];
  sprintf(filename, "/tmp/libfuzzer.%d", getpid());

  FILE *fp = fopen(filename, "wb");
  if (!fp) {
    return 0;
  }
  fwrite(data, size, 1, fp);
  fclose(fp);

  hid_t fuzz_h5_id = H5Fopen(filename, H5F_ACC_RDWR, H5P_DEFAULT);
  if (fuzz_h5_id != H5I_INVALID_HID) {
    hid_t dataset_id = H5Dopen2(fuzz_h5_id, "dsetname", H5P_DEFAULT);
    if (dataset_id != H5I_INVALID_HID) {
      // Fix: Use H5Dread instead of H5D__virtual_read
      hsize_t dims[1] = {1};
      herr_t status = H5Dread(dataset_id, H5T_NATIVE_INT, H5S_ALL, H5S_ALL, H5P_DEFAULT, dims);
      if (status < 0) {
        // Handle read error
      }
      H5Dclose(dataset_id);
    }
    H5Fclose(fuzz_h5_id);
  }
  return 0;
}