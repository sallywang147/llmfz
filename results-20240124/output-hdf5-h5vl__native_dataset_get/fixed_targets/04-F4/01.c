#include "hdf5.h"
#include "H5VL__native_dataset.h"

extern "C" {
#include "H5VL__native_dataset_get.h"
}

int main() {
  hid_t file_id = H5Fopen("test.h5", H5F_ACC_RDONLY, H5P_DEFAULT);
  if (file_id < 0) {
    return -1;
  }

  hid_t dataset_id = H5Dopen(file_id, "dataset", H5P_DEFAULT);
  if (dataset_id < 0) {
    return -1;
  }

  H5VL__native_dataset_get(dataset_id);

  H5Dclose(dataset_id);
  H5Fclose(file_id);

  return 0;
}