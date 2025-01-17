#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <string>
#include <vector>

#include "hdf5.h"

extern "C" {
#include "H5VLnative.h"
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
      struct H5VL_dataset_get_args_t args;
      args.dataset_id = dataset_id;
      args.op_type = H5VL_DATASET_GET_OP_GET_CHUNK;
      char *result = nullptr;
      size_t result_size = 0;
      int ret = H5VL__native_dataset_get(nullptr, &args, &result_size, &result);
      if (ret == 0) {
        free(result);
      }
      H5Dclose(dataset_id);
    }
    H5Fclose(fuzz_h5_id);
  }
  return 0;
}