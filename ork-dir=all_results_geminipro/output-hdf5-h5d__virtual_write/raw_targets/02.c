#include <cstdint>
#include <cstdio>
#include <cstring>
#include <string>
#include <vector>

#include "hdf5.h"

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
      hid_t filespace_id = H5Dget_space(dataset_id);
      if (filespace_id != H5I_INVALID_HID) {
        hsize_t num_elements;
        int ndims = H5Sget_simple_extent_ndims(filespace_id);
        hsize_t* dims = new hsize_t[ndims];
        H5Sget_simple_extent_dims(filespace_id, dims, &num_elements);

        hid_t memspace_id = H5Screate_simple(ndims, dims, nullptr);
        if (memspace_id != H5I_INVALID_HID) {
          H5D_io_info_t io_info;
          io_info.addr = nullptr;
          io_info.u.wbuf = new uint8_t[num_elements];
          io_info.u.wbuf_size = num_elements;

          H5D_dset_io_info_t dset_io_info;
          dset_io_info.type_id = H5T_NATIVE_UCHAR;
          dset_io_info.raw_data_buf = nullptr;
          dset_io_info.raw_data_size = 0;
          dset_io_info.raw_offset = 0;
          dset_io_info.raw_data_total_size = 0;

          int ret = H5D__virtual_write(&io_info, &dset_io_info);
          if (ret < 0) {
            fprintf(stderr, "H5D__virtual_write failed with error code %d\n",
                    ret);
          }

          delete[] io_info.u.wbuf;
          H5Sclose(memspace_id);
        }
        H5Sclose(filespace_id);
        delete[] dims;
      }
      H5Dclose(dataset_id);
    }
    H5Fclose(fuzz_h5_id);
  }
  return 0;
}