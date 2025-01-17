 #include <fuzzer/FuzzedDataProvider.h>

#include <hdf5.h>
#include <stddef.h>
#include <stdint.h>
#include <string.h>

extern int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider stream(data, size);

  struct H5VL_dataset_get_args_t args;
  args.pdataset = stream.ConsumeBytesAsString(stream.ConsumeIntegralInRange(0, 1024));
  args.op = stream.ConsumeIntegral<int>();
  args.n = stream.ConsumeIntegral<size_t>();
  args.buf = stream.ConsumeBytesAsString(stream.ConsumeIntegralInRange(0, 1024));
  args.buf_size = stream.ConsumeIntegral<size_t>();

  int ret = H5VL__native_dataset_get(args.pdataset, &args, args.n, &args.buf);
  if (ret < 0) {
    return 0;
  }

  return 0;
}