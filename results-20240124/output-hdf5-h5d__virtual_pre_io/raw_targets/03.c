 #include <stddef.h>
#include <stdint.h>
#include <hdf5.h>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  struct H5D_t *dset_ptr = (struct H5D_t *)malloc(sizeof(struct H5D_t));
  struct H5O_storage_virtual_t *storage_ptr = (struct H5O_storage_virtual_t *)malloc(sizeof(struct H5O_storage_virtual_t));
  struct H5S_t *space_ptr = (struct H5S_t *)malloc(sizeof(struct H5S_t));
  struct H5S_t *mem_space_ptr = (struct H5S_t *)malloc(sizeof(struct H5S_t));
  size_t *nbytes_ptr = (size_t *)malloc(sizeof(size_t));

  H5D__virtual_pre_io(dset_ptr, storage_ptr, space_ptr, mem_space_ptr, nbytes_ptr);

  free(dset_ptr);
  free(storage_ptr);
  free(space_ptr);
  free(mem_space_ptr);
  free(nbytes_ptr);

  return 0;
}