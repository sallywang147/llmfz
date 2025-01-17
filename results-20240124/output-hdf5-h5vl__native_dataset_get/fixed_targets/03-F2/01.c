#include <stddef.h>
#include <stdint.h>
#include <string.h>

#include "hdf5.h"

extern "C" {
int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  char *path = (char *)data;
  size_t path_len = size;

  struct H5VL_dataset_get_args_t args;
  memset(&args, 0, sizeof(args));
  args.path = path;
  args.path_len = path_len;

  char *buf = nullptr;
  size_t buf_len = 0;
  int ret = H5VL__native_dataset_get(path, &args, buf_len, &buf);
  if (ret == 0) {
    free(buf);
  }
  return 0;
}
}