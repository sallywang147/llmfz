#include "hdf5.h"

extern "C" {
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
}

extern "C" {
hid_t H5Dopen2(hid_t loc_id, const char *name, hid_t dapl_id);
herr_t H5D__virtual_write(struct H5D_io_info_t *io_info, struct H5D_dset_io_info_t *dset_io_info);
}

extern "C" {
hid_t H5Fopen(const char *name, unsigned flags, hid_t fapl_id);
hid_t H5Dclose(hid_t dset_id);
hid_t H5Fclose(hid_t file_id);
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

  extern "C" {
    hid_t fuzz_h5_id = H5Fopen(filename, H5F_ACC_RDWR, H5P_DEFAULT);
    if (fuzz_h5_id != H5I_INVALID_HID) {
      hid_t dataset_id = H5Dopen2(fuzz_h5_id, "dsetname", H5P_DEFAULT);
      if (dataset_id != H5I_INVALID_HID) {
        struct H5D_io_info_t io_info;
        struct H5D_dset_io_info_t dset_io_info;
        H5D__virtual_write(&io_info, &dset_io_info);
        H5Dclose(dataset_id);
      }
      H5Fclose(fuzz_h5_id);
    }
  }
  return 0;
}