#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hdf5.h"

extern "C" {
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
}

extern int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
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
      struct H5D_t *dataset = (struct H5D_t *)dataset_id;
      size_t space_id = H5D__get_space(dataset);
      H5Sclose(space_id);
      H5Dclose(dataset_id);
    }
    H5Fclose(fuzz_h5_id);
  }
  return 0;
}