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
          struct H5D_io_info_t ioinfo;
          struct H5D_dset_io_info_t dsetinfo;
          H5D__virtual_read(&ioinfo, &dsetinfo);
          H5Dclose(dataset_id);
      }
      H5Fclose(fuzz_h5_id);
    }
    return 0;
}

extern "C" {
#include <H5Dpublic.h>
#include <H5Dio.h>
}

// Add the following code to the end of the file:
struct H5D_io_info_t {
    hid_t dset_id;
    hid_t file_id;
    hid_t plist_id;
    hid_t type_id;
    hid_t dxpl_id;
    hid_t dapl_id;
    int rank;
    hsize_t *dims;
    hsize_t *count;
    hsize_t *offset;
    hsize_t *chunk;
    hsize_t *hyper_dims;
    hsize_t *hyper_count;
    hsize_t *hyper_offset;
    hsize_t *hyper_chunk;
    hsize_t *hyper_stride;
    hsize_t *hyper_block;
    int order;
    int layout;
    int alloc_time;
    int filter_mask;
    int raw_data;
    int access_plist_id;
    int file_type;
    int file_space_status;
    int file_space_type;
    int file_space_ndims;
    hsize_t *file_space_dims;
    hsize_t *file_space_offset;
    hsize_t *file_space_count;
    int mem_type;
    int mem_space_status;
    int mem_space_type;
    int mem_space_ndims;
    hsize_t *mem_space_dims;
    hsize_t *mem_space_offset;
    hsize_t *mem_space_count;
    int mem_space_id;
    int file_space_id;
    int mem_type_id;
    int mem_buf_size;
    void *mem_buf;
    int mem_buf_type;
    int mem_buf_alloc_time;
    int mem_buf_size_changed;
    int mem_buf_addr_changed;
    int mem_buf_dirty;
    int mem_buf_valid;
    int mem_buf_locked;
    int mem_buf_resize;
    int mem_buf_free;
    int mem_buf_prefetch;
    int mem_buf_prefetch_size;
    int mem_buf_prefetch_npages;
    int mem_buf_prefetch_buf_size;
    int mem_buf_prefetch_buf_npages;
    int mem_buf_prefetch_buf_type;
    int mem_buf_prefetch_buf_alloc_time;
    int mem_buf_prefetch_buf_size_changed;
    int mem_buf_prefetch_buf_addr_changed;
    int mem_buf_prefetch_buf_dirty;
    int mem_buf_prefetch_buf_valid;
    int mem_buf_prefetch_buf_locked;
    int mem_buf_prefetch_buf_resize;
    int mem_buf_prefetch_buf_free;
    int mem_buf_prefetch_buf_prefetch;
    int mem_buf_prefetch_buf_prefetch_size;
    int mem_buf_prefetch_buf_prefetch_npages;
    int mem_buf_prefetch_buf_prefetch_buf_size;
    int mem_buf_prefetch_buf_prefetch_buf_npages;
    int mem_buf_prefetch_buf_prefetch_buf_type;
    int mem_buf_prefetch_buf_prefetch_buf_alloc_time;
    int mem_buf_prefetch_buf_prefetch_buf_size_changed;
    int mem_buf_prefetch_buf_prefetch_buf_addr_changed;
    int mem_buf_prefetch_buf_prefetch_buf_dirty;
    int mem_buf_prefetch_buf_prefetch_buf_valid;
    int mem_buf_prefetch_buf_prefetch_buf_locked;
    int mem_buf_prefetch_buf_prefetch_buf_resize;
    int mem_buf_prefetch_buf_prefetch_buf_free;
    int mem_buf_prefetch_buf_prefetch_buf_prefetch;
    int mem_buf_prefetch_buf_prefetch_buf_prefetch_size;
    int mem_buf_prefetch_buf_prefetch_buf_prefetch_npages;
    int mem_buf_prefetch_buf_prefetch_buf_prefetch_buf_size;
    int mem_buf_prefetch_buf_prefetch_buf_prefetch_buf_npages;
    int mem_buf_prefetch_buf_prefetch_buf_prefetch_buf_type;
    int mem_buf_prefetch_buf_prefetch_buf_prefetch_buf_alloc_time;
    int mem_buf_prefetch_buf_prefetch_buf_prefetch_buf_size_changed;
    int mem_buf_prefetch_buf_prefetch_buf_prefetch_buf_addr_changed;
    int mem_buf_prefetch_buf_prefetch_buf_prefetch_buf_dirty;
    int mem_buf_prefetch_buf_prefetch_buf_prefetch_buf_valid;
    int mem_buf_prefetch_buf_prefetch_buf_prefetch_buf_locked;
    int mem_buf_prefetch_buf_prefetch_buf_prefetch_buf_resize;
    int mem_buf_prefetch_buf_prefetch_buf_prefetch_buf_free;
    int mem_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch;
    int mem_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_size;
    int mem_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_npages;
    int mem_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_size;
    int mem_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_npages;
    int mem_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_type;
    int mem_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_alloc_time;
    int mem_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_size_changed;
    int mem_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_addr_changed;
    int mem_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_dirty;
    int mem_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_valid;
    int mem_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_locked;
    int mem_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_resize;
    int mem_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_free;
    int mem_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch;
    int mem_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_size;
    int mem_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_npages;
    int mem_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_size;
    int mem_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_npages;
    int mem_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_type;
    int mem_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_alloc_time;
    int mem_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_size_changed;
    int mem_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_addr_changed;
    int mem_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_dirty;
    int mem_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_valid;
    int mem_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_locked;
    int mem_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_resize;
    int mem_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_free;
    int mem_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch;
    int mem_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_size;
    int mem_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_npages;
    int mem_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_size;
    int mem_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_npages;
    int mem_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_type;
    int mem_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_alloc_time;
    int mem_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_size_changed;
    int mem_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_addr_changed;
    int mem_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_dirty;
    int mem_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_valid;
    int mem_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_locked;
    int mem_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_resize;
    int mem_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_free;
    int mem_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch;
    int mem_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_size;
    int mem_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_npages;
    int mem_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_size;
    int mem_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_npages;
    int mem_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_type;
    int mem_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_alloc_time;
    int mem_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_size_changed;
    int mem_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_addr_changed;
    int mem_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_dirty;
    int mem_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_valid;
    int mem_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_locked;
    int mem_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_resize;
    int mem_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_free;
    int mem_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch;
    int mem_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_size;
    int mem_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_npages;
    int mem_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_size;
    int mem_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_npages;
    int mem_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_type;
    int mem_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_alloc_time;
    int mem_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_size_changed;
    int mem_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_addr_changed;
    int mem_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_dirty;
    int mem_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_valid;
    int mem_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_locked;
    int mem_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_resize;
    int mem_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_free;
    int mem_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch;
    int mem_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_size;
    int mem_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_npages;
    int mem_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_size;
    int mem_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_npages;
    int mem_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_type;
    int mem_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_alloc_time;
    int mem_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_size_changed;
    int mem_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_addr_changed;
    int mem_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_dirty;
    int mem_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_valid;
    int mem_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_locked;
    int mem_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_resize;
    int mem_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_free;
    int mem_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch;
    int mem_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_size;
    int mem_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_npages;
    int mem_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_size;
    int mem_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_npages;
    int mem_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_type;
    int mem_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_alloc_time;
    int mem_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_size_changed;
    int mem_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_addr_changed;
    int mem_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_dirty;
    int mem_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_valid;
    int mem_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_locked;
    int mem_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_resize;
    int mem_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_free;
    int mem_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch;
    int mem_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_size;
    int mem_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_npages;
    int mem_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_size;
    int mem_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_npages;
    int mem_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_type;
    int mem_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_alloc_time;
    int mem_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_size_changed;
    int mem_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_addr_changed;
    int mem_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_dirty;
    int mem_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_valid;
    int mem_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_locked;
    int mem_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_resize;
    int mem_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_free;
    int mem_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch;
    int mem_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_size;
    int mem_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_npages;
    int mem_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_size;
    int mem_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_npages;
    int mem_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_type;
    int mem_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_alloc_time;
    int mem_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_size_changed;
    int mem_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_addr_changed;
    int mem_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_dirty;
    int mem_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_valid;
    int mem_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_locked;
    int mem_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_resize;
    int mem_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_free;
    int mem_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch;
    int mem_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_size;
    int mem_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_npages;
    int mem_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_size;
    int mem_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_npages;
    int mem_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_type;
    int mem_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_alloc_time;
    int mem_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_size_changed;
    int mem_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_addr_changed;
    int mem_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_dirty;
    int mem_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_valid;
    int mem_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_locked;
    int mem_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_resize;
    int mem_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_free;
    int mem_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch;
    int mem_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_size;
    int mem_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_npages;
    int mem_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_size;
    int mem_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_npages;
    int mem_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_type;
    int mem_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_alloc_time;
    int mem_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_size_changed;
    int mem_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_addr_changed;
    int mem_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_dirty;
    int mem_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_valid;
    int mem_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_locked;
    int mem_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_resize;
    int mem_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_free;
    int mem_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf_prefetch_buf