 #include "hdf5.h"

extern int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size)
{
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
      hid_t  dataset_id = H5Dopen2(fuzz_h5_id, "dsetname", H5P_DEFAULT);
      if (dataset_id != H5I_INVALID_HID) {
          struct H5VL_dataset_get_args_t get_args;
          get_args.fapl_id = H5P_DEFAULT;
          get_args.dataset_id = dataset_id;
          get_args.buf_size = 1024;
          get_args.buf = (char *)malloc(get_args.buf_size);
          H5VL__native_dataset_get(NULL, &get_args, 0, NULL);
          free(get_args.buf);
          H5Dclose(dataset_id);
      }
      H5Fclose(fuzz_h5_id);
    }
    return 0;
}