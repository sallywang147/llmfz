#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include "hdf5.h"

extern "C" {
int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  // Create a temporary file to store the fuzzed data.
  char filename[256];
  sprintf(filename, "/tmp/libfuzzer.%d", getpid());

  FILE *fp = fopen(filename, "wb");
  if (!fp) {
    return 0;
  }
  fwrite(data, size, 1, fp);
  fclose(fp);

  // Open the HDF5 file.
  hid_t file_id = H5Fopen(filename, H5F_ACC_RDWR, H5P_DEFAULT);
  if (file_id < 0) {
    return 0;
  }

  // Create a dataset.
  hid_t dataset_id = H5Dcreate2(file_id, "dsetname", H5T_STD_I32BE, H5S_SCALAR, H5P_DEFAULT, H5P_DEFAULT, H5P_DEFAULT);
  if (dataset_id < 0) {
    H5Fclose(file_id);
    return 0;
  }

  // Create a virtual storage object.
  H5O_storage_virtual_t virtual_storage;
  virtual_storage.type = H5O_STORAGE_VIRTUAL;
  virtual_storage.u.virtual_.data = (void *)data;
  virtual_storage.u.virtual_.size = size;

  // Call the function to be fuzzed.
  int ret = H5D__virtual_pre_io((H5D_t *)dataset_id, &virtual_storage, NULL, NULL, NULL);

  // Close the dataset and file.
  H5Dclose(dataset_id);
  H5Fclose(file_id);

  // Return the result of the function call.
  return ret;
}
}