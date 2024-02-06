#include <fuzzer/FuzzedDataProvider.h>
#include "H5VLnative_private.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider stream(data, size);

  // Initialize the arguments for H5VL__native_dataset_get
  H5VL_dataset_get_args_t args;
  args.op_type = stream.ConsumeIntegral<H5VL_dataset_get_t>();
  args.args.get_space_status.space_status = stream.ConsumeIntegral<int>();

  // Prepare the buffer for the dataset name
  std::string dataset_name = stream.ConsumeRandomLengthString();
  
  // Prepare the buffer for the output
  char* out = nullptr;
  size_t out_size = 0;

  // Call the target function
  H5VL__native_dataset_get(dataset_name.data(), &args, out_size, &out);

  return 0;
}