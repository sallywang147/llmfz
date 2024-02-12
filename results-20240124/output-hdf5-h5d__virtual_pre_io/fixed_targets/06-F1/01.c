#include "hdf5.h"

extern "C" {
#include <H5DSpublic.h>
#include <H5Fpublic.h>
#include <H5Opublic.h>
#include <H5Spublic.h>
}

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
        struct H5D_t *dset_ptr = (struct H5D_t *)dataset_id;
        struct H5O_storage_virtual_t *storage_virtual_ptr = (struct H5O_storage_virtual_t *)dset_ptr->shared->layout.storage.u.virt;
        struct H5S_t *space_id_ptr = (struct H5S_t *)dset_ptr->shared->space;
        struct H5S_t *space_id_ptr2 = (struct H5S_t *)dset_ptr->shared->space;
        size_t *count_ptr = (size_t *)dset_ptr->shared->layout.storage.u.virt->count;
        int ret = H5D__virtual_pre_io(dset_ptr, storage_virtual_ptr, space_id_ptr, space_id_ptr2, count_ptr);
        if (ret != 0) {
          return 0;
        }
        H5Dclose(dataset_id);
      }
      H5Fclose(fuzz_h5_id);
    }
    return 0;
}