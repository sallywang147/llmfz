#include "hdf5.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider stream(data, size);
  char *filename = stream.ConsumeRandomLengthString().c_str();
  struct H5VL_dataset_get_args_t dataset_get_args;
  dataset_get_args.fapl_id = H5P_DEFAULT;
  dataset_get_args.dataset_id = H5I_INVALID_HID;
  dataset_get_args.dtype_id = H5I_INVALID_HID;
  dataset_get_args.space_id = H5I_INVALID_HID;
  dataset_get_args.buf = nullptr;
  dataset_get_args.buf_size = 0;
  size_t *nalloc = new size_t;
  *nalloc = 0;
  char **buf_ptr = new char*;
  *buf_ptr = nullptr;
  int ret = H5VL__native_dataset_get(filename, &dataset_get_args, nalloc, buf_ptr);
  if (ret == -1) {
    return 0;
  }
  free(dataset_get_args.buf);
  delete nalloc;
  delete buf_ptr;
  return 0;
}