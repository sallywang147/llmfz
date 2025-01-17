#include <algorithm>
#include <hdf5.h>
#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>
#include <fuzzer/FuzzedDataProvider.h>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider stream(data, size);

  char *path = stream.ConsumeRandomLengthString().c_str();
  struct H5VL_dataset_get_args_t args;
  args.dataset_name = path;
  args.args_len = stream.ConsumeIntegral<size_t>();
  args.args_buf = (char *)stream.ConsumeBytes<uint8_t>(args.args_len).data();
  char **result = nullptr;
  int ret = H5VL__native_dataset_get(path, &args, args.args_len, result);
  free(path);
  free(args.args_buf);
  free(result);
  return ret;
}